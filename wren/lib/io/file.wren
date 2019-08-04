class File {
    /**
     * The system-dependent path-separator character.
     * On UNIX systems the value of this
     * field is <code>'/'</code>; on Microsoft Windows systems it is <code>'\\'</code>.
     *
     */
    static PathSeparator { "/" }
    /**
     * Returns the length of this abstract pathname's prefix.
     * For use by FileSystem classes.
     */
    PrefixLength { _prefixLength }

    
    /**
     * Returns the name of the file or directory denoted by this abstract
     * pathname.  This is just the last name in the pathname's name
     * sequence.  If the pathname's name sequence is empty, then the empty
     * string is returned.
     *
     */
    Name { _name }
    /**
     * Returns the pathname string of this abstract pathname's parent, or
     * <code>null</code> if this pathname does not name a parent directory.
     *
     */
    Parent { parent }
    /**
     * Converts this abstract pathname into a pathname string.  The resulting
     * string uses the {@link #separator default name-separator character} to
     * separate the names in the name sequence.
     *
     */
    Path { _path }
    /**
     * Tests whether the file or directory denoted by this abstract pathname
     * exists.
     *
     */
    construct Create(path) {
        _path = path
    }

    construct Create(parent, child) {
        _path = parent + "/" + child
    }


    Exists() {

    }
    /**
     * Tests whether the file denoted by this abstract pathname is a
     * directory.
     */
    IsDirectory() {

    }
    /**
     * Tests whether the file denoted by this abstract pathname is a normal
     * file.  A file is <em>normal</em> if it is not a directory and, in
     * addition, satisfies other system-dependent criteria.  Any non-directory
     * file created by a Java application is guaranteed to be a normal file.
     *
     */
    IsFile() {

    }
 }

