#pragma once
#include <iostream>
#include <vector>
#include <string>

class CountInversions {
public:
	int bruteForce(std::vector<int>& testArr) {
		size_t size = testArr.size();
		int noInversions = 0;

		for (size_t i = 0; i < size; i++) {
			for (size_t j = i; j < size; j++) {
				if (testArr[i] > testArr[j]) {
					noInversions++;
				}
			}
		}
		std::cout << "No of invesrions brute force: " << noInversions << std::endl;
		return noInversions;
	}

	void countInversion(std::vector<int>& arr) {
		std::vector<int> out;
		out = arr;
		std::cout << "initial: ";
		for (auto& k : out) {
			std::cout << k << " ";
		}
		std::cout << "\n";
		mergeSort(arr, 0, arr.size()-1, out);

		std::cout << "final: ";
		for (auto& k : arr) {
			std::cout << k << " ";
		}
		std::cout << "\n";
	}

	void mergeSort(std::vector<int>& arr, int start, int end, std::vector<int>& out) {
		if (end <= start) {
			return;
		}
		auto mid = start + (end-start) / 2;
		print("start: " + std::to_string(start) + " mid: " + std::to_string(mid) + " end: " + std::to_string(end));
		mergeSort(arr, start, mid, out);
		mergeSort(arr, mid+1, end, out);
		merge(start, mid, end, arr, out);
		for (auto& k : arr) {
			std::cout << k << " ";
		}
		std::cout << "\n";
	}	

	void merge(int start, int mid, int end, std::vector<int>& arr, std::vector<int>& out) {
		int i = start;
		int j = mid+1;
		
		for (int i = start; i <= end; i++) {
			out[i] = arr[i];
		}
		for (int n = start; n <= end; n++) {
			if (i > mid) {
				arr[n] = out[j];
				j++;
			}
			else if (j > end) {
				arr[n] = out[i];
				i++;
			}
			else if(out[j] < out[i]) {
				arr[n] = out[j];
				j++;
			}
			else {
				arr[n] = out[i];
				i++;
			}						
		}
	}

	void testMerge(std::vector<int>& arr) {
		int mid = arr.size() / 2;
		int i = 0;
		int j = mid;
		int end = arr.size();

		std::vector<int> out;

		for (int n = 0; n < arr.size(); n++) {
			if (arr[i] < arr[j] && i<mid) {
				out.push_back(arr[i]);
				i++;
			}
			else if (arr[j] < arr[i] && j<end) {
				out.push_back(arr[j]);
				j++;
			}
			// Insert rest of upper nodes if first half is ended 
			if (i >= mid) {
				for (int k = j; j < end; j++) {
					out.push_back(arr[j]);
				}
				break;
			}
			// Insert rest of first half nodes if second half is ended
			if (j >= end) {
				for (int k = i; k < mid; i++) {
					out.push_back(arr[k]);
				}
				break;
			}
		}

		arr = out;
	}

	template<typename T>
	void print(T name) {
		std::cout << name << std::endl;
	}
};