#!/usr//bin/python3

import argparse
import math

def covering_radius_lower_bound(n, k):
    target = 1 << (n - k)  # 2^(n-k)
    cumulative = 0

    for r in range(n + 1):
        cumulative += math.comb(n, r)
        if cumulative >= target:
            return r
    return n


def rm_dimension(m, r):
    return sum(math.comb(m, i) for i in range(r + 1))


def main():
    parser = argparse.ArgumentParser(description="Sphere covering bound for Reed-Muller codes")
    parser.add_argument("r", type=int, help="order of RM code")
    parser.add_argument("m", type=int, help="number of variables")

    args = parser.parse_args()

    n = 2 ** args.m
    k = rm_dimension(args.m, args.r)

    R = covering_radius_lower_bound(n, k)

    print(f"R <= ρ({args.r},{args.m}) = {R}")

if __name__ == "__main__":
    main()


