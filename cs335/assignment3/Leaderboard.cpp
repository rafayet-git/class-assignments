#include "Leaderboard.hpp"

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

/**
 * @brief Uses a mixture of quickselect/quicksort to
 *        select and sort the top 10% of players with O(log N) memory
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
RankingResult Offline::quickSelectRank(std::vector<Player>& players){
  if (players.empty())
    return RankingResult({},{},0);

  int tops = std::floor(0.1*players.size());
  if (tops == 0) tops++;
  tops = players.size() - tops; // quickselect to find position tops
  
  auto start_time = std::chrono::high_resolution_clock::now(); // timer start
  std::nth_element(players.begin(), players.begin()+tops, players.end());
  // sort
  quickSort(players, tops-1, players.size()-1);
  auto end_time = std::chrono::high_resolution_clock::now(); // timer end
  std::chrono::duration<double, std::milli> duration = end_time - start_time;
  return RankingResult(std::vector<Player>(players.begin()+tops,players.end()), {}, duration.count());
}

/**
 * @brief Helper function for quickSelectRank to perform quick sort.
 *
 * @param players A reference to the vector of Player objects to be ranked
 * @param left The index to the leftmost item in the partition.
 * @param right The index pointing to the rightmost item in the partition.
 *
 * @post A portion of the players is sorted.
 */
void Offline::quickSort(std::vector<Player>& players, int left, int right){
  // based off 7.17
   if (left < right){
    // Just using median pivot
    int pi = (left+right)/2;
    std::swap(players[pi],players[right]);
    Player& pivot = players[right];

    int i = left-1, j = right;
    for(;;){
      while(players[++i] < pivot){}
      while(pivot < players[--j]){}
      if (i < j)
        std::swap(players[i],players[j]);
      else break;
    }
    std::swap(players[i],players[right]);
    quickSort(players,left,i-1);
    quickSort(players,i+1,right);

  }
}

/**
 * @brief A helper method that replaces the minimum element
 * in a min-heap with a target value & preserves the heap
 * by percolating the new value down to its correct position.
 *
 * Performs in O(log N) time.
 *
 * @pre The range [first, last) is a min-heap.
 *
 * @param first An iterator to a vector of Player objects
 *      denoting the beginning of a min-heap
 *      NOTE: Unlike the textbook, this is *not* an empty slot
 *      used to store temporary values. It is the root of the heap.
 *
 * @param last An iterator to a vector of Player objects
 *      denoting one past the end of a min-heap
 *      (i.e. it is not considering a valid index of the heap)
 *
 * @param target A reference to a Player object to be inserted into the heap
 * @post
 * - The vector slice denoted from [first,last) is a min-heap
 *   into which `target` has been inserted.
 * - The contents of `target` is not guaranteed to match its original state
 *   (ie. you may move it).
 */
void Online::replaceMin(PlayerIt first, PlayerIt last, Player& target){
  int hole = 0;
  int child = 0;
  int length = last - first;

  for(; hole * 2 + 1 < length; hole = child){
    child = hole * 2 + 1;
    if (child + 1 < length && *(first + child+1) < *(first + child))
      child++;
    if (*(first + child) < target)
      *(first + hole) = std::move(*(first + child));
    else
      break;  
  }
  *(first + hole) = std::move(target); 
  
}

/**
 * @brief Exhausts a stream of Players (ie. until there are none left) such that we:
 * 1) Maintain a running collection of the <reporting_interval> highest leveled players
 * 2) Record the Player level after reading every <reporting_interval> players
 *    representing the minimum level required to be in the leaderboard at that point.
 *
 * @note You should use NOT use a priority-queue.
 *       Instead, use a vector, the STL heap operations, & `replaceMin()`
 *
 * @param stream A stream providing Player objects
 * @param reporting_interval The frequency at which to record cutoff levels
 * @return A RankingResult in which:
 * - top_       -> Contains the top <reporting_interval> Players read in the stream in
 *                 sorted (least to greatest) order
 * - cutoffs_   -> Maps player count milestones to minimum level required at that point
 *                 including the minimum level after ALL players have been read, regardless
 *                 of being a multiple of the reporting interval
 * - elapsed_   -> Contains the duration (ms) of the selection/sorting operation
 *                 excluding fetching the next player in the stream
 *
 * @post All elements of the stream are read until there are none remaining.
 *
 * @example Suppose we have:
 * 1) A stream with 132 players
 * 2) A reporting interval of 50
 *
 * Then our resulting RankingResult might contain something like:
 * top_ = { Player("RECLUSE", 994), Player("WYLDER", 1002), ..., Player("DUCHESS", 1399) }, with length 50
 * cutoffs_ = { 50: 239, 100: 992, 132: 994 } (see RankingResult explanation)
 * elapsed_ = 0.003 (Your runtime will vary based on hardware)
 */
RankingResult Online::rankIncoming(PlayerStream& stream, const size_t& reporting_interval){
  if (stream.remaining() == 0)
    return RankingResult({},{},0);
  std::vector<Player> players;
  std::unordered_map<size_t, size_t> cutoffs;
  int count = 0;

  auto start_time = std::chrono::high_resolution_clock::now(); // timer start
  // make players into min heap when at reporting_interval, then use replaceMin
  // or if stream < reporting_interval
  while (stream.remaining() > 0){
    Player next = stream.nextPlayer();
    count++;
    if (players.size() < reporting_interval){
      players.push_back(next);
      std::push_heap(players.begin(), players.end(), std::greater<Player>());
    } else {
      if (next > players[0]){
        replaceMin(players.begin(), players.end(), next);
      }
    }
    if (count % reporting_interval == 0){
      cutoffs[count] = players[0].level_;
    }
  }

  if (count % reporting_interval != 0)
    cutoffs[count] = players[0].level_;

  std::sort_heap(players.begin(), players.end(), std::greater<Player>());
  std::reverse(players.begin(), players.end());
  
  auto end_time = std::chrono::high_resolution_clock::now(); // timer end
  std::chrono::duration<double, std::milli> duration = end_time - start_time;
  
  return RankingResult(players, cutoffs, duration.count());
}
