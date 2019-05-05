#include <iostream>
#include <functional>
#include <chrono>
#include <string>
// The following are included ONLY to check if the array is sorted.
// I do not use any STL sorting algorithms. (See sort.h)
#include <algorithm>
#include <iterator>

#include "sort.h"
#include "simple_rng.h"

constexpr size_t COLLECTION_SIZE = 10'000;
constexpr int NO_INSERTION_SORT = 0;
constexpr int WITH_INSERTION_SORT = 20;

std::function<int(int[], int, int)> middle = sort::middle_pivot<int>;
std::function<int(int[], int, int)> median = sort::median_pivot<int>;

// Use the Object Lifetime Paradigm
// The timer begins as soon as an instance is produced.
struct Timer
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    std::string operation;

    Timer() : operation("Timer"), start(std::chrono::high_resolution_clock::now()) {}

    Timer(std::string operation)
        : operation(operation), start(std::chrono::high_resolution_clock::now()) {}

    // Display results at the end of the instance's lifetime, in milliseconds.
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        std::cout << operation << " took " << ms << "ms " << std::endl;
    }
};

// Container for a randomized array. The contents of the array are randomized every time
// the object is initialized
struct array_container
{
    static int collection[COLLECTION_SIZE];

    // Populate the array with random numbers on every instantiation.
    array_container() { std::generate(collection + 0, collection + COLLECTION_SIZE, simple_rng::generate_random_int); }
};
int array_container::collection[COLLECTION_SIZE] = {};

void sort_with_middle_pivot()
{
    array_container a;
    Timer timer("Sorting with middle pivot (No insertion sort)");

    sort::quick_sort(a.collection, COLLECTION_SIZE, NO_INSERTION_SORT, middle);
}

void sort_with_median_pivot()
{
    array_container a;
    Timer timer("Sorting with median pivot (No insertion sort)");

    sort::quick_sort(a.collection, COLLECTION_SIZE, NO_INSERTION_SORT, median);
}

void sort_with_middle_pivot_and_insertion()
{
    array_container a;
    Timer timer("Sorting with middle pivot (With insertion sort)");

    sort::quick_sort(a.collection, COLLECTION_SIZE, WITH_INSERTION_SORT, middle);
}

void sort_with_median_pivot_and_insertion()
{
    array_container a;
    Timer timer("Sorting with median pivot (With insertion sort)");

    sort::quick_sort(a.collection, COLLECTION_SIZE, WITH_INSERTION_SORT, median);
}

void is_successful(std::string type)
{
    std::cout << type << " sort "
        << (std::is_sorted(std::begin(array_container::collection), std::end(array_container::collection)) ? "successful" : "unsuccessful")
        << '\n';
}

int main()
{
    sort_with_middle_pivot();
    is_successful("Middle");
    std::cout << std::endl;

    sort_with_median_pivot();
    is_successful("Median");
    std::cout << std::endl;

    sort_with_middle_pivot_and_insertion();
    is_successful("Middle + Insertion");
    std::cout << std::endl;

    sort_with_median_pivot_and_insertion();
    is_successful("Median + Insertion");
    std::cout << std::endl;

    system("pause");

    return 0;
}