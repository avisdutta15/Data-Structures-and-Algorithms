#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/*
    Given number of pages in n different books and m students. The books are arranged
    in ascending order of number of pages. Every student is assigned to read some
    consecutive books. The task is to assign books in such a way that the maximum number
    of pages assigned to a student is minimum.

    Example :

    Input : pages[] = {12, 34, 67, 90}
            m = 2
    Output : 113
    Explanation:
    There are 2 number of students. Books can be distributed
    in following fashion :
    1) [12] and [34, 67, 90]
        Max number of pages is allocated to student
        2 with 34 + 67 + 90 = 191 pages
    2) [12, 34] and [67, 90]
        Max number of pages is allocated to student
        2 with 67 + 90 = 157 pages
    3) [12, 34, 67] and [90]
        Max number of pages is allocated to student
        1 with 12 + 34 + 67 = 113 pages

    Of the 3 cases, Option 3 has the minimum pages = 113.



    Approach 1:
        [Naive Approach] By Iterating Over All Possible Page Limits
        The idea is to iterate over all possible page limits, or maximum pages that can be allocated to a student.

        The minimum possible page limit is the highest page count among all books, as the book with the most pages
        must be assigned to some student.

        The maximum possible page limit is the sum of pages of all books, It is in the case when all books are given
        to a single student.

        To find the number of students that will be allocated books for a page limit, we start assigning books to
        the first student until the page limit is reached, then we move to the next student and so on. As soon as
        we find the first page limit with which we can allocate books to all k students, we will return it.


        Why minimum pages? Because, we want to minimize the maximum pages a student can read.
        Example:
        pages = [10, 20, 30, 40]  students = 2
        [10] and [20, 30, 40]   =   10 / 90 => maximum pages a student will read = 90
        [10,20] and [30, 40]    =   30 / 70 => maximum pages a student will read = 70
        [10, 20, 30] and [40]   =   60 / 40 => maximum pages a student will read = 60

        Minimum of [90, 70, 60] = 60

        Because our goal is to evaluate the "maximum number of pages a student has to read", 
        we have to accept that some student is inevitably going to get stuck with that biggest book.

        TC: -
        O(N * (sum(arr[])-max(arr[])+1)), where
            N = size of the array,
            sum(arr[]) = sum of all array elements,
            max(arr[]) = maximum of all array elements.

        Reason: We are applying loop on [max(arr[]), sum(arr[])]. Inside the loop, we are calling
        the checkIfWithThisPageLimitBooksCanBeAllocated() function for the value of ‘mid’. Now,
        inside the checkIfWithThisPageLimitBooksCanBeAllocated() function,
        we are using a loop that runs for N times.

    Approach 2:
        The maximum number of pages(page limit) that a student can be allocated has a monotonic property:

        If, at a page limit p, books cannot be allocated to all k students, then we need to reduce the page
        limit to ensure more students receive books.

        If, at a page limit p, we can allocate books to more than k students, then we need to increase the
        page limit so that fewer students are allocated books.

        Therefore, we can apply binary search to minimize the maximum pages a student can be allocated. To
        check the number of students that can be allotted books for any page limit, we start assigning books
        to the first student until the page limit is reached, then move to the next student.

        O(N * log(sum(arr[])-max(arr[])+1)), where
            N = size of the array,
            sum(arr[]) = sum of all array elements,
            max(arr[]) = maximum of all array elements.

        Reason: We are applying binary search on [max(arr[]), sum(arr[])]. Inside the loop, we are calling
        the checkIfWithThisPageLimitBooksCanBeAllocated() function for the value of ‘mid’. Now,
        inside the checkIfWithThisPageLimitBooksCanBeAllocated() function,
        we are using a loop that runs for N times.

        SEARCH SPACE : MAX Pages ..... Sum Of All Pages

*/

// Naive
class Solution1 {
private:
    bool checkIfWithThisPageLimitBooksCanBeAllocated(vector<int>& books, int numStudents, int numOfPagesAStudentCanRead) {

        // Starting from the first student
        int studentsCount = 1;
        int currentPages = 0;

        for (int i = 0; i < books.size(); i++) {
            // If adding the current book exceeds the page 
            // limit, assign the book to the next student and increment student count
            if (currentPages + books[i] > numOfPagesAStudentCanRead) {
                currentPages = books[i];
                studentsCount++;
                //if studentsCount exceed then return false
                if (studentsCount > numStudents)
                    return false;
            }
            else {
                currentPages += books[i];
            }
        }

        // If books can assigned to all students then
        // return true
        return true;
    }

public:
    int bookAllocation(vector<int>& books, int numStudents, int numBooks) {

        // If number of students are more than total books
        // then allocation is not possible
        if (numStudents > numBooks)
            return -1;


        // Minimum and maximum possible page limits
        int minPageLimit = *max_element(books.begin(), books.end());
        int maxPageLimit = accumulate(books.begin(), books.end(), 0);

        // Iterating over all possible page limits
        for (int pageLimit = minPageLimit; pageLimit <= maxPageLimit; pageLimit++) {

            // Return the first page limit with we can
            // allocate books to all numStudents students
            if (checkIfWithThisPageLimitBooksCanBeAllocated(books, numStudents, pageLimit))
                return pageLimit;
        }

        //if not possible then return -1
        return -1;
    }
};

// Binary Search
class Solution2 {
private:
    bool checkIfWithThisPageLimitBooksCanBeAllocated(vector<int>& books, int numStudents, int numOfPagesAStudentCanRead) {

        // Starting from the first student
        int studentsCount = 1;
        int currentPages = 0;

        for (int i = 0; i < books.size(); i++) {
            // If adding the current book exceeds the page 
            // limit, assign the book to the next student and increment student count
            if (currentPages + books[i] > numOfPagesAStudentCanRead) {
                currentPages = books[i];
                studentsCount++;
                //if studentsCount exceed then return false
                if (studentsCount > numStudents)
                    return false;
            }
            else {
                currentPages += books[i];
            }
        }

        // If books can assigned to all students then
        // return true
        return true;
    }

public:
    int bookAllocation(vector<int>& books, int numStudents, int numBooks) {
        if (numStudents > numBooks)
            return -1;

        int minPageLimit = *max_element(books.begin(), books.end());
        int maxPageLimit = accumulate(books.begin(), books.end(), 0);

        int lo = minPageLimit;
        int hi = maxPageLimit;
        int mid = 0, numOfPagesAStudentCanRead = 0;
        int pageLimit = -1;

        //find the minimum number of pages from the page search space as [start , end]
        //that each student can read.
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            numOfPagesAStudentCanRead = mid;

            if (checkIfWithThisPageLimitBooksCanBeAllocated(books, numStudents, numOfPagesAStudentCanRead)) {
                pageLimit = mid;    //if you get a valid configuration with this numOfPagesAStudentCanRead
                //then save it and search for smaller number of pages i.e. minimize the pages
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        return pageLimit;
    }
};

int main() {
    // Naive
    Solution1 obj1;
    int numStudents = 2;
    int numBooks = 4;
    vector<int> books = { 12, 34, 67, 90 };  //ith book contains book[i] pages
    cout << obj1.bookAllocation(books, numStudents, numBooks) << endl;

    // Binary Search
    Solution2 obj2;
    numStudents = 2;
    numBooks = 4;
    books = { 12, 34, 67, 90 };  //ith book contains book[i] pages
    cout << obj2.bookAllocation(books, numStudents, numBooks) << endl;

}
