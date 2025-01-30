#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <algorithm>
#include <set>


class Movie {
public:
    Movie(std::string title, std::string genre, std::string rating, int year, double score)
        : title(std::move(title)), genre(std::move(genre)), 
          rating(std::move(rating)), year(year), score(score) {}

   
    const std::string& getTitle() const { return title; }
    const std::string& getGenre() const { return genre; }
    const std::string& getRating() const { return rating; }
    int getYear() const { return year; }
    double getScore() const { return score; }

    
    void display() const {
        std::cout << "Title: " << title 
                  << " | Genre: " << genre 
                  << " | Rating: " << rating 
                  << " | Year: " << year 
                  << " | Score: " << score << "/10" 
                  << std::endl;
    }

private:
    std::string title;
    std::string genre;
    std::string rating;
    int year;
    double score;
};


class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual std::shared_ptr<Movie> next() = 0;
    virtual void reset() = 0;
};


class MovieCollection {
public:
    virtual ~MovieCollection() = default;
    virtual std::shared_ptr<Iterator> createIterator() = 0;
    virtual void addMovie(std::shared_ptr<Movie> movie) = 0;
};


class GenreIterator : public Iterator {
public:
    GenreIterator(const std::vector<std::shared_ptr<Movie>>& movies) 
        : movies(movies), currentIndex(0) {}

    bool hasNext() const override {
        return currentIndex < movies.size();
    }

    std::shared_ptr<Movie> next() override {
        if (hasNext()) {
            return movies[currentIndex++];
        }
        return nullptr;
    }

    void reset() override {
        currentIndex = 0;
    }

private:
    const std::vector<std::shared_ptr<Movie>>& movies;
    size_t currentIndex;
};


class FilteredIterator : public Iterator {
public:
    FilteredIterator(const std::vector<std::shared_ptr<Movie>>& allMovies,
                    const std::set<std::string>& ratings = {},
                    const std::set<std::string>& genres = {},
                    int yearFrom = 0,
                    int yearTo = 9999)
        : allMovies(allMovies), currentIndex(0),
          ratings(ratings), genres(genres),
          yearFrom(yearFrom), yearTo(yearTo) {
        
        filterMovies();
    }

    bool hasNext() const override {
        return currentIndex < filteredMovies.size();
    }

    std::shared_ptr<Movie> next() override {
        if (hasNext()) {
            return filteredMovies[currentIndex++];
        }
        return nullptr;
    }

    void reset() override {
        currentIndex = 0;
    }

private:
    void filterMovies() {
        for (const auto& movie : allMovies) {
            bool matches = true;

            
            if (!ratings.empty() && ratings.find(movie->getRating()) == ratings.end()) {
                matches = false;
            }

            
            if (!genres.empty() && genres.find(movie->getGenre()) == genres.end()) {
                matches = false;
            }

            
            if (movie->getYear() < yearFrom || movie->getYear() > yearTo) {
                matches = false;
            }

            if (matches) {
                filteredMovies.push_back(movie);
            }
        }
    }

    const std::vector<std::shared_ptr<Movie>>& allMovies;
    std::vector<std::shared_ptr<Movie>> filteredMovies;
    size_t currentIndex;
    std::set<std::string> ratings;
    std::set<std::string> genres;
    int yearFrom;
    int yearTo;
};

// Movie Catalog class to manage all movies
class MovieCatalog : public MovieCollection {
public:
    void addMovie(std::shared_ptr<Movie> movie) override {
        allMovies.push_back(movie);
        moviesByGenre[movie->getGenre()].push_back(movie);
    }

    std::shared_ptr<Iterator> createIterator() override {
        return std::make_shared<GenreIterator>(allMovies);
    }

    std::shared_ptr<Iterator> createGenreIterator(const std::string& genre) {
        return std::make_shared<GenreIterator>(moviesByGenre[genre]);
    }

    std::shared_ptr<Iterator> createFilteredIterator(
        const std::set<std::string>& ratings = {},
        const std::set<std::string>& genres = {},
        int yearFrom = 0,
        int yearTo = 9999) {
        return std::make_shared<FilteredIterator>(allMovies, ratings, genres, yearFrom, yearTo);
    }

private:
    std::vector<std::shared_ptr<Movie>> allMovies;
    std::map<std::string, std::vector<std::shared_ptr<Movie>>> moviesByGenre;
};


void testMovieRentalPlatform() {
    MovieCatalog catalog;

    
    catalog.addMovie(std::make_shared<Movie>("The Matrix", "Action", "R", 1999, 8.7));
    catalog.addMovie(std::make_shared<Movie>("Inception", "Action", "PG-13", 2010, 8.8));
    catalog.addMovie(std::make_shared<Movie>("The Godfather", "Drama", "R", 1972, 9.2));
    catalog.addMovie(std::make_shared<Movie>("Pulp Fiction", "Drama", "R", 1994, 8.9));
    catalog.addMovie(std::make_shared<Movie>("The Hangover", "Comedy", "R", 2009, 7.7));
    catalog.addMovie(std::make_shared<Movie>("Superbad", "Comedy", "R", 2007, 7.6));
    catalog.addMovie(std::make_shared<Movie>("Iron Man", "Action", "PG-13", 2008, 7.9));
    catalog.addMovie(std::make_shared<Movie>("The Dark Knight", "Action", "PG-13", 2008, 9.0));

    // Test 1: Iterate over all Action movies
    std::cout << "\n=== Action Movies ===\n";
    auto actionIterator = catalog.createGenreIterator("Action");
    while (actionIterator->hasNext()) {
        actionIterator->next()->display();
    }

    // Test 2: Iterate over R-rated movies from 2000-2010
    std::cout << "\n=== R-Rated Movies (2000-2010) ===\n";
    auto filteredIterator = catalog.createFilteredIterator(
        {"R"},  // ratings
        {},     // genres (empty = all genres)
        2000,   // yearFrom
        2010    // yearTo
    );
    while (filteredIterator->hasNext()) {
        filteredIterator->next()->display();
    }

    // Test 3: Iterate over PG-13 Action and Drama movies
    std::cout << "\n=== PG-13 Action and Drama Movies ===\n";
    auto genreFilteredIterator = catalog.createFilteredIterator(
        {"PG-13"},             // ratings
        {"Action", "Drama"},    // genres
        0,                      // yearFrom
        9999                    // yearTo
    );
    while (genreFilteredIterator->hasNext()) {
        genreFilteredIterator->next()->display();
    }

    // Test 4: Movies from the 2000s
    std::cout << "\n=== Movies from 2000-2009 ===\n";
    auto yearFilteredIterator = catalog.createFilteredIterator(
        {},    
        {},     
        2000,   
        2009    
    );
    while (yearFilteredIterator->hasNext()) {
        yearFilteredIterator->next()->display();
    }
}

int main() {
    testMovieRentalPlatform();
    return 0;
}