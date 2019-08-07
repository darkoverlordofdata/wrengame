foreign class Path { 
    construct new(path) {}

    // An absolute path, starting with "/" on POSIX systems, a drive letter on
    // Windows, etc.
    foreign static Absolute

    // An explicitly relative path, starting with "./" or "../".
    foreign static Relative

    // A path that has no leading prefix, like "foo/bar".
    foreign static Simple

    // the current working directory
    foreign static Cwd 

    // Categorizes what form a path is.
    foreign static Type(string)

    // Strips off the last component of the path name.
    foreign DirName()

    // Strips off the file extension from the last component of the path.
    foreign RemoveExtension()

    // Appends [string] to [path].
    foreign Join(string)

    // Appends [c] to the path, growing the buffer if needed.
    foreign AppendChar(c)

    // Appends [string] to the path, growing the buffer if needed.
    foreign AppendString(string)

    // Simplifies the path string as much as possible.
    //
    // Applies and removes any "." or ".." components, collapses redundant "/"
    // characters, and normalizes all path separators to "/".
    foreign Normalize()

    // Allocates a new string exactly the right length and copies this path to it.
    foreign ToString()
}

