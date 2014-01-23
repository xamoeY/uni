#!/usr/bin/env python3

import random

chances_of_failure = [1, 5, 10, 25, 50, 75, 98, 99]

for chance in chances_of_failure:
    tries_list = []
    for i in range(1000000):
        tries = 0
        success = False

        # Try transfer until it succeeds
        while not success:
            if random.randint(0, 100) < chance:
                # Failure
                tries += 1
            else:
                # Success
                success = True

                # Put number of attempts into list so we can calculate average
                tries_list.append(tries)

    average = sum(tries_list) / float(len(tries_list))
    print("Average number of tries for {}% failure chance: {}".format(chance, average))
