#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Rating {
    int userId;
    int movieId;
    float rating;
};

// Calculate the cosine similarity between two users
float cosineSimilarity(const unordered_map<int, float>& v1, const unordered_map<int, float>& v2) {
    // Check if the users have rated any common movies
    bool commonMovies = false;
    for (const auto& p : v1) {
        int movieId = p.first;
        if (v2.count(movieId)) {
            commonMovies = true;
            break;
        }
    }
    if (!commonMovies) {
        return 0;
    }

    // Calculate the dot product, norm of v1, and norm of v2
    float dotProduct = 0;
    float norm1 = 0;
    float norm2 = 0;
    for (const auto& p : v1) {
        int movieId = p.first;
        if (v2.count(movieId)) {
            float rating1 = p.second;
            float rating2 = v2.at(movieId);
            dotProduct += rating1 * rating2;
            norm1 += rating1 * rating1;
            norm2 += rating2 * rating2;
        }
    }

    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}
// Read ratings from the input file and store them in a vector
vector<Rating> readRatings(const string& filename) {
    vector<Rating> ratings;

    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Rating r;
        ss >> r.userId >> r.movieId >> r.rating;
        ratings.push_back(r);
    }

    return ratings;
}

// Find the ratings for the test set using the IBCF method
unordered_map<int, float> findTestRatings(const vector<Rating>& ratings, const vector<pair<int, int>>& testSet) {
    unordered_map<int, float> testRatings;

    // Create a map of users to their ratings
    unordered_map<int, unordered_map<int, float>> userRatings;
    for (const Rating& r : ratings) {
        userRatings[r.userId][r.movieId] = r.rating;
    }

    // Create a map of movies to their ratings
    unordered_map<int, vector<float>> movieRatings;
    for (const Rating& r : ratings) {
        movieRatings[r.movieId].push_back(r.rating);
    }

    // Find the ratings for the test set
    for (const pair<int, int>& p : testSet) {
        int userId = p.first;
        int movieId = p.second;
        float sum = 0;
        float weightSum = 0;

        // Calculate the weighted average of the ratings
        for (const Rating& r : ratings) {
            if (r.movieId == movieId) {
                float similarity = cosineSimilarity(userRatings[userId], userRatings[r.userId]);
                if (similarity > 0) {
                    sum += similarity * r.rating;
                    weightSum += similarity;
                }
            }
        }
        testRatings[userId] = weightSum == 0 ? 0 : sum / weightSum;
    }

    return testRatings;
}

int main() {
    // Read the ratings from the input file
    vector<Rating> ratings = readRatings("ratings.txt");

    // Read the test set from the input file
    vector<pair<int, int>> testSet;
    ifstream file("testset.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int userId;
        int movieId;
        ss >> userId >> movieId;
        testSet.push_back({ userId, movieId });
    }

    // Find the ratings for the test set
    unordered_map<int, float> testRatings = findTestRatings(ratings, testSet);

    // Output the test ratings
    for (const pair<int, float>& p : testRatings) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}