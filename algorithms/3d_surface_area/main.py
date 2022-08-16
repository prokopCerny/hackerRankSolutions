#!/bin/python3

# Found at https://www.hackerrank.com/challenges/3d-surface-area/problem

import math
import os
import random
import re
import sys

#
# Complete the 'surfaceArea' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY A as parameter.
#

def surfaceArea(A, rows, cols):
    prev_row_sub = [0 for _ in range(cols)]
    
    surface_area = 0
    
    for i, row in enumerate(A):
        if i == rows:
            break
        prev_col_sub = 0
        for j, cur_height in enumerate(row):
            if j == cols:
                break
            left_sub = prev_col_sub
            right_sub = min(cur_height, A[i][j+1])
            top_sub = prev_row_sub[j]
            down_sub = min(cur_height, A[i+1][j])
            
            prev_col_sub = right_sub
            prev_row_sub[j] = down_sub
            
            cur_sides = 2 + 4 * cur_height - left_sub - right_sub - top_sub - down_sub
            
            surface_area += cur_sides
            
    return surface_area
            
    

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    H = int(first_multiple_input[0])

    W = int(first_multiple_input[1])

    A = []

    for _ in range(H):
        A.append(list(map(int, input().rstrip().split())) + [0])

    A.append([0 for _ in range(W)])
    
    result = surfaceArea(A, H, W)

    fptr.write(str(result) + '\n')

    fptr.close()
