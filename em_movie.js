mergeInto(LibraryManager.library, {
    em_play_movie: function(namePtr) {
        var name = UTF8ToString(namePtr);
        self.postMessage({ action: 'play-movie', name: name });
        self._moviePlaying = true;
    },
    em_movie_playing: function() {
        return self._moviePlaying ? 1 : 0;
    }
});
