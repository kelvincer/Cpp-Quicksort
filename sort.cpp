#include <iostream>
#include <array>
#include <span>

enum Side
{
    RIGHT,
    LEFT
};

bool searchLessThanItem(std::span<int>, int &, int &start, int &end);

bool searchGreaterThanItem(std::span<int>, int &, int &start, int &end);

void quicksort(std::span<int> arr, int start, int end)
{
    if (arr.size() == 1 || arr.size() == 0)
    {
        return;
    } 

    int startIt = 0;
    int endIt = 0;
    int index = 0;
    Side side = Side::RIGHT;
    bool found = true;

    while (true)
    {
        switch (side)
        {
        case RIGHT:
        {
            found = searchLessThanItem(arr, index, startIt, endIt);
            side = Side::LEFT;
            break;
        }
        case LEFT:
        {
            found = searchGreaterThanItem(arr, index, startIt, endIt);
            side = Side::RIGHT;
            break;
        }
        }

        std::cout << "\nf: " << found << std::endl;

        if (!found)
        {
            break;
        }

        std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "i = " << index << std::endl;
    }

    quicksort(std::span(arr.begin(), index), 0, 0);
    quicksort(std::span(arr.begin() + index + 1, arr.size() - index - 1), 0, 0);
}

bool searchLessThanItem(std::span<int> arr, int &index, int &start, int &end)
{
    for (auto it = arr.end() - 1 - end; it != arr.begin() + start; it--)
    {
        if (*it < arr[index])
        {
            int temp = *it;
            *it = arr[index];
            arr[index] = temp;
            index = std::distance(arr.begin(), it);
            end = arr.size() - index;
            return true;
        }
    }
    return false;
}

bool searchGreaterThanItem(std::span<int> arr, int &index, int &start, int &end)
{
    for (auto it = arr.begin() + start; it != arr.end() - end; it++)
    {
        if (*it > arr[index])
        {
            int temp = *it;
            *it = arr[index];
            arr[index] = temp;
            index = std::distance(arr.begin(), it);
            start = index;
            return true;
        }
    }
    return false;
}

int main(void)
{
    std::array<int, 12> arr = {-20, 100, 37, 2, 6, 4, 89, 8, 10, 12, 68, 45};

    quicksort(arr, 0, 0);

    std::cout << "Final: ";
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}