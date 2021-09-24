#include <iostream>
#include <vector>
#include <random>
#include <optional>
class Play2048 {
private:
    std::vector<std::vector<std::optional<int>>> m_grid;
    std::size_t m_size;
    bool m_game_over;

    int generate_random_number(int range) const {
        std::random_device random_device;
        std::default_random_engine engine(random_device());
        std::uniform_int_distribution<int> distribution(0, range);
        return distribution(engine);
    }
    std::pair<int, int> generate_index() const {
        return { generate_random_number(m_size - 1), generate_random_number(m_size - 1) };
    }

    int generate_value() const {
        int guess = generate_random_number(100);
        return guess < 85 ? 2 : 4;
    }

    void add_value() {
        int tries = 0;
        while (tries < m_size * m_size) {
            auto [x, y] = generate_index();
            if (!m_grid[x][y].has_value()) {
                m_grid[x][y] = generate_value();
                return;
            }
            tries++;
        }
        m_game_over = true;
    }

    void helper_right_collapes(std::vector<std::optional<int>>& row) {
        std::vector<std::optional<int>>::reverse_iterator first = row.rend();
        for(auto i = row.rbegin(); i != row.rend(); ++i) {
            if(first == row.rend()) {
                first = i;
                continue;
            }

            if(first->value() == i->value()){
                *first = first->value() + i->value();
                *i = {};
                first++;
            }

        }
    }

public:
    Play2048(size_t size = 5) :
        m_grid(std::vector<std::vector<std::optional<int>>>(size, std::vector<std::optional<int>>(size))),
        m_size(size),
        m_game_over(false) {
        for (size_t i = 0; i < 26; i++) {
            add_value();
        }
    }

    void collapes_right() {
        
    }
    bool is_game_over() const {
        return m_game_over;
    }



    void print_grid() const {
        for (auto row : m_grid) {
            for (auto col : row) {
                std::cout << col.value_or(0) << " ";
            }
            std::cout << std::endl;
        }
    }
};

class Game {

};


int main() {
    Play2048 game;
    game.print_grid();
    std::cout << std::endl;
    std::cout << game.is_game_over();
} 