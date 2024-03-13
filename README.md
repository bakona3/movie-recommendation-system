# movie-recommendation-system
This C++ code is designed to recommend movie ratings to users based on their past ratings using Item-Based Collaborative Filtering (IBCF). The program involves several steps, from reading user ratings and test sets from files, calculating similarities between users, to predicting ratings for movies in a test set. Let's break down the code into its key components:

Includes and Namespace:

The code starts by including necessary headers for input/output operations, file handling, string manipulation, unordered maps (hash tables), vectors, algorithms, and mathematical functions. It then uses the std namespace to avoid prefixing standard library types with std::.

Struct Definition:

A struct named Rating is defined to hold a single rating, consisting of a user ID, a movie ID, and the rating value itself. This struct simplifies the process of working with user ratings.

Cosine Similarity Function:

cosineSimilarity is a function that calculates the similarity between two users based on the movies they've both rated. It takes as input two unordered maps (unordered_map<int, float>), representing the ratings of two users, where keys are movie IDs and values are rating scores. The function first checks for common movies rated by both users. If no common movies are found, it returns 0, indicating no similarity. Otherwise, it calculates the cosine similarity based on the dot product of the ratings vectors and the norms of these vectors. Cosine similarity measures the cosine of the angle between two vectors in a multi-dimensional space, effectively evaluating how similar the users' preferences are.

Read Ratings Function:

readRatings is a function that reads user ratings from a file and stores them in a vector of Rating structs. It opens a file with the given filename, reads each line, extracts user ID, movie ID, and rating, and adds them to the vector.

Find Test Ratings Function:

findTestRatings predicts ratings for a set of user-movie pairs (the test set). It takes as input the complete list of ratings and the test set, which is a vector of pairs where each pair contains a user ID and a movie ID. The function constructs two maps: one mapping users to their movie ratings and another mapping movies to the ratings they received. It then iterates over the test set, for each user-movie pair, it calculates a weighted average of ratings that similar users have given the movie, using the cosine similarity between users as weights.

Main Function:

The main function orchestrates the program's flow:


It reads the complete list of ratings from "ratings.txt" using the readRatings function.

It reads the test set from "testset.txt", consisting of user-movie pairs for which the program will predict ratings.

It calls findTestRatings to predict ratings for the test set based on the ratings read from the file and the similarities between users.

Finally, it outputs the predicted ratings for each user-movie pair in the test set.

This program exemplifies a simple yet powerful approach to recommending content based on user preferences, a foundational technique in many recommendation systems.
