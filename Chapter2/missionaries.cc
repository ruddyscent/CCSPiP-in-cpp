/**
 * @file missionaries.cc
 * @brief 
 * @details
 * @copyright Copyright 2023 Kyungwon Chun
 * 
 * @license Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <functional>

#include "generic_search.h"

const int MAX_NUM = 3;

class MCState {
public:
    MCState(int missionaries, int cannibals, bool boat) :
        _wm(missionaries),
        _wc(cannibals),
        _em(MAX_NUM - missionaries),
        _ec(MAX_NUM - cannibals),
        _boat(boat) {}

    bool is_legal() const {
        if (_wm < _wc && _wm > 0) {
            return false;
        }
        if (_em < _ec && _em > 0) {
            return false;
        }
        return true;
    }

    bool goal_test(const MCState& s) const {
        return s.is_legal() && s._em == MAX_NUM && s._ec == MAX_NUM;
    }

    std::vector<MCState> successors(const MCState& s) const {
        std::vector<MCState> sucs;
        if (s._boat) { // boat on west bank
            if (s._wm > 1) {
                sucs.push_back(MCState(s._wm - 2, s._wc, !s._boat));
            }
            if (s._wm > 0) {
                sucs.push_back(MCState(s._wm - 1, s._wc, !s._boat));
            }
            if (s._wc > 1) {
                sucs.push_back(MCState(s._wm, s._wc - 2, !s._boat));
            }
            if (s._wc > 0) {
                sucs.push_back(MCState(s._wm, s._wc - 1, !s._boat));
            }
            if (s._wc > 0 && s._wm > 0) {
                sucs.push_back(MCState(s._wm - 1, s._wc - 1, !s._boat));
            }
        } else { // boat on east bank
            if (s._em > 1) {
                sucs.push_back(MCState(s._wm + 2, s._wc, !s._boat));
            }
            if (s._em > 0) {
                sucs.push_back(MCState(s._wm + 1, s._wc, !s._boat));
            }
            if (s._ec > 1) {
                sucs.push_back(MCState(s._wm, s._wc + 2, !s._boat));
            }
            if (s._ec > 0) {
                sucs.push_back(MCState(s._wm, s._wc + 1, !s._boat));
            }
            if (s._ec > 0 && s._em > 0) {
                sucs.push_back(MCState(s._wm + 1, s._wc + 1, !s._boat));
            }
        }
        std::vector<MCState> legal_sucs;
        for (const auto& suc : sucs) {
            if (suc.is_legal()) {
                legal_sucs.push_back(suc);
            }
        }
        return legal_sucs;
    }
    
    bool operator<(const MCState& other) const {
        if (_wm != other._wm) {
            return _wm < other._wm;
        }
        if (_wc != other._wc) {
            return _wc < other._wc;
        }
        if (_em != other._em) {
            return _em < other._em;
        }
        if (_ec != other._ec) {
            return _ec < other._ec;
        }
        return _boat < other._boat;
    }

    friend std::ostream& operator<<(std::ostream& os, const MCState& state) {
        os << "On the west bank there are " << state._wm << " missionaries and " << state._wc << " cannibals.\n"
           << "On the east bank there are " << state._em << " missionaries and " << state._ec << " cannibals.\n"
           << "The boat is on the " << (state._boat ? "west" : "east") << " bank.";
        return os;
    }

    friend void display_solution(const std::vector<MCState>& path);

private:
    int _wm; // west bank missionaries
    int _wc; // west bank cannibals
    int _em; // east bank missionaries
    int _ec; // east bank cannibals
    bool _boat; // true if boat is on west bank 
};

void display_solution(const std::vector<MCState>& path) {
    if (path.empty()) { // sanity check
        return;
    }
    MCState old_state = path.front();
    std::cout << old_state << std::endl;
    for (int i = 1; i < path.size(); i++) {
        if (path[i]._boat) {
            std::cout << old_state._em - path[i]._em << " missionaries and "
                      << old_state._ec - path[i]._ec << " cannibals moved from the east bank to the west bank.\n";
        } else {
            std::cout << old_state._wm - path[i]._wm << " missionaries and "
                      << old_state._wc - path[i]._wc << " cannibals moved from the west bank to the east bank.\n";
        }
        std::cout << path[i] << std::endl;
        old_state = path[i];
    }
}

int main(int argc, char* argv[]) {
    MCState start(MAX_NUM, MAX_NUM, true);

    auto solution = bfs<MCState>(start, 
        std::bind_front(&MCState::goal_test, &start), 
        std::bind_front(&MCState::successors, &start));

    if (!solution) {
        std::cout << "No solution found!" << std::endl;
    } else {
        auto path = node_to_path(solution);
        display_solution(path);
    }

    return EXIT_SUCCESS;
}