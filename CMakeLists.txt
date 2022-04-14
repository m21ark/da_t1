cmake_minimum_required(VERSION 3.10)
project(da_t1)

set(CMAKE_CXX_STANDARD 17)

set(CREATE_EXE TRUE)

add_executable(da_t1 main.cpp

        src/read_files.cpp include/read_files.h
        src/knapsack.cpp include/knapsack.h
        src/express_deliveries.cpp include/express_deliveries.h src/OptimizeProfit.cpp include/OptimizeProfit.h
        src/OptimizeProfit.cpp
        src/express_deliveries.cpp include/express_deliveries.h include/menu.h src/menu.cpp
        include/timer.h src/timer.cpp
        src/express_deliveries.cpp include/express_deliveries.h include/menu.h src/menu.cpp
        include/timer.h src/timer.cpp include/OptimizeNumberOfDeliveries.h
        src/OptimizeNumberOfDeliveries.cpp
        include/Objects.h src/Memento.cpp include/Memento.h)


