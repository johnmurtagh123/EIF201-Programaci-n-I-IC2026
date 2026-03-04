#pragma once

void invertirVector(int array[], int size, int invertida[]) {

	for (int i = 0; i < size; i++) {
		invertida[i] = array[size - i - 1];
	}
}