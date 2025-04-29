#include "PlayerStream.hpp"
/**
 * @brief Constructs a VectorPlayerStream from a vector of Players.
 *
 * Initializes the stream with a sequence of Player objects matching the
 * contents of the given vector.
 *
 * @param players The vector of Player objects to stream.
 */
VectorPlayerStream::VectorPlayerStream(const std::vector<Player>& players){

}
/**
 * @brief Retrieves the next Player in the stream.
 *
 * @return The next Player object in the sequence.
 * @post Updates members so a subsequent call to nextPlayer() yields the Player
 * following that which is returned.

 * @throws std::runtime_error If there are no more players remaining in the stream.
 */
Player VectorPlayerStream::nextPlayer(){

}
/**
 * @brief Returns the number of players remaining in the stream.
 *
 * @return The count of players left to be read.
 */
size_t VectorPlayerStream::remaining() const{ // see how many instances remaining to be fetched

}
