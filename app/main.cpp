#include "../include/MetricsRegistry.h"
#include "../include/MetricsWriter.h"
#include "../include/CounterMetric.h"
#include "../include/AverageMetric.h"
#include <iostream>
#include <vector>
#include <thread>
#include <random>

void workerFunc(MetricsRegistry& registry, const int workerID) {
    std::cout << "Поток " << workerID << " стартовал" << "\n";

    auto* cpu = registry.getMetric<AverageMetric>("CPU");
    auto* rps = registry.getMetric<CounterMetric>("HTTP requests RPS");

    if (!cpu || !rps) {
        std::cerr << "Метрики не найдены" << "\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> cpuRand(0.0, 2.0);
    std::uniform_int_distribution<> rpuRand(1, 10);

    for (int i = 0; i < 20; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        cpu->add(cpuRand(gen));
        rps->increment(rpuRand(gen));
    }

    std::cout << "Поток " << workerID << " закончил работу." << "\n";
}

int main() {
    try {
        MetricsRegistry registry;

        registry.registerMetric( "CPU", std::make_unique<AverageMetric>("CPU"));
        registry.registerMetric( "HTTP requests RPS", std::make_unique<CounterMetric>("HTTP requests RPS"));

        MetricsWriter writer(registry, std::chrono::seconds(1), "metrics.txt");

        std::cout << "Симуляция работы двух потоков" << std::endl;

        std::vector<std::thread> threads;
        threads.emplace_back(workerFunc, std::ref(registry), 1);
        threads.emplace_back(workerFunc, std::ref(registry), 2);

        for (auto& t : threads) {
            t.join();
        }

        std::cout << "Симуляция окончена, можно посмотреть логи в metrics.txt" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}