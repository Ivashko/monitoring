#include <iostream>
#include "tsl/robin_map.h"
#include <unordered_map>
#include <random>
#include "benchmark/benchmark.h"

int gen (int max)
{
    static std::mt19937 prng (1233);
    return std::uniform_int_distribution <> (0, max)(prng);
}

struct Place
{
    int room;
    bool event;
};


template <typename T>
T data_gen(int x)
{
    T mapA;
    for (int i = 0; i < x; i++)
    {
        Place p;
        p.room = gen(100);
        p.event = 1;
        mapA[i] = p;
    }
    return mapA;
}

template<typename T>
static void BM_map(benchmark::State& state)
{
    T mapA = data_gen<T>(state.range(0));
    for (auto _:state)
    {
            int id = gen(state.range(0));
            int  r = gen(100);
            bool e = gen(1);
            Place pA;
            pA = mapA[id];


            if ((pA.room == r) and (pA.event == 1) and (e == 0))
             {
                     pA.event = 0;
                     pA.room = -1;
                     mapA[id] = pA;
             }
            else if ((pA.room == -1) and (e == 1))
                {
                    pA.event = 1;
                    pA.room = r;
                    mapA[id] = pA;
                }


        }

}

//BENCHMARK_TEMPLATE(BM_map, tsl::robin_map<int, Place>) -> Arg(5461) -> Arg(43690) -> Arg (349525) -> Arg (89478485);
//BENCHMARK_TEMPLATE(BM_map, std::unordered_map<int, Place>) -> Arg(5461) -> Arg(43690) -> Arg (349525) -> Arg (89478485);
