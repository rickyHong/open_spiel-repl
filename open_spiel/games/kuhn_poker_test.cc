// Copyright 2019 DeepMind Technologies Ltd. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "open_spiel/games/kuhn_poker.h"

#include "open_spiel/algorithms/get_all_states.h"
#include "open_spiel/spiel_utils.h"
#include "open_spiel/tests/basic_tests.h"

namespace open_spiel {
namespace kuhn_poker {
namespace {

namespace testing = open_spiel::testing;

void BasicKuhnTests() {
  testing::LoadGameTest("kuhn_poker");
  testing::ChanceOutcomesTest(*LoadGame("kuhn_poker"));
  testing::RandomSimTest(*LoadGame("kuhn_poker"), 100);
  for (int players = 3; players <= 5; players++) {
    testing::RandomSimTest(
        *LoadGame("kuhn_poker", {{"players", GameParameter(players)}}), 100);
  }
}

void CountStates() {
  KuhnGame game({});
  auto states = algorithms::GetAllStates(game, /*depth_limit=*/-1,
                                         /*include_terminals=*/true,
                                         /*include_chance_states=*/false);
  // 6 deals * 9 betting sequences (-, p, b, pp, pb, bp, bb, pbp, pbb) = 54
  SPIEL_CHECK_EQ(states.size(), 54);
}

}  // namespace
}  // namespace kuhn_poker
}  // namespace open_spiel

int main(int argc, char **argv) {
  open_spiel::kuhn_poker::BasicKuhnTests();
  open_spiel::kuhn_poker::CountStates();
  open_spiel::testing::CheckChanceOutcomes(open_spiel::kuhn_poker::KuhnGame(
      {{"players", open_spiel::GameParameter(3)}}));
  open_spiel::testing::RandomSimTest(open_spiel::kuhn_poker::KuhnGame({}),
                                     /*num_sims=*/10);
}
