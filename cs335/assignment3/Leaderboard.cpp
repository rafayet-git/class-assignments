#include "Leaderboard.hpp"
#include <algorithm>

/**
 * @brief Constructor for RankingResult with top players, cutoffs, and elapsed time.
 *
 * @param top Vector of top-ranked Player objects, in sorted order.
 * @param cutoffs Map of player count thresholds to minimum level cutoffs.
 *   NOTE: This is only ever non-empty for Online::rankIncoming().
 *         This parameter & the corresponding member should be empty
 *         for all Offline algorithms.
 * @param elapsed Time taken to calculate the ranking, in seconds.
 */
RankingResult::RankingResult(const std::vector<Player>& top, const std::unordered_map<size_t, size_t>& cutoffs, double elapsed)
    : top_ { top }
    , cutoffs_ { cutoffs }
    , elapsed_ { elapsed }
{
}

/**
 * @brief Uses an early-stopping version of heapsort to
 *        select and sort the top 10% of players in-place
 *        (excluding the returned RankingResult vector)
 *
 * @param players A reference to the vector of Player objects to be ranked
 * @return A Ranking Result object whose
 * - top_ vector -> Contains the top 10% of players from the input in sorted order (ascending)
 * - cutoffs_    -> Is empty
 * - elapsed_    -> Contains the duration (ms) of the selection/sorting operation
 *
 * @post The order of the parameter vector is modified.
 */
RankingResult Offline::heapRank(std::vector<Player>& players){
  if (players.empty())
    return RankingResult({},{},0);

  int tops = std::floor(0.1*players.size());
  if (tops == 0) tops++;
  
  auto start_time = std::chrono::high_resolution_clock::now(); // timer start
  std::make_heap(players.begin(), players.end());
  for (auto it = players.end(); it != players.end()-tops; --it){
    std::pop_heap(players.begin(), it);
  }
  auto end_time = std::chrono::high_resolution_clock::now(); // timer end
  std::chrono::duration<double, std::milli> duration = end_time - start_time;
  
  // Sorted items are at end of players
  return RankingResult(std::vector<Player>(players.end()-tops,players.end()), {}, duration.count());
  
}
