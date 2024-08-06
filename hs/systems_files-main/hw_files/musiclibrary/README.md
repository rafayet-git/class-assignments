# Systems-Project1-MyTunes-Template

### Linked List Part
insert nodes at the front
- done, fully working

insert nodes in order
- done, believe it to be fully working (has helper function too)

print the entire list
- done, working

find and return a pointer to a node based on artist and song name
- done, working

find and return a pointer to the first song of an artist based on artist name
- done, working

Return a pointer to random element in the list.
- done (there's a second version, randomNode, which doesn't work because srand is set within the function body, but let's ignore it)

remove a single specified node from the list
- done, i believe it works as it should

free the entire list
- done, works if you have the call in the form of ```pointer = freelist(pointer);```

### Library Part

Allocate enough memory for 27 linked lists, make sure each entry is an empty list.
- done

Add song nodes.
- done

Search for a song given song and artist name (return a pointer).
- done, working

Search for an artist (return a pointer).
- done, working

Print out all the entries under a certain letter.
- done, working

Print out all the songs of a certain artist
- done, working

Print out the entire library.
- done, working

Shuffle - print out a series of randomly chosen songs.
- done
- i was able to do it in a way that doesn't appear to modify the list, but still avoids repeats

Delete a song
- done, working

Clear out all the linked lists in the library.
- done, working
- if i undertsood correctly, it should just empty the songlist of all songs
