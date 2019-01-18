#pragma once

struct AABB {
    ///<summary>
    /// <code>
    ///   O(x,y) ---w-----o
    ///      |            |
    ///      |            |
    ///      h            h
    ///      |            |
    ///      |            |
    ///      o -----w-----o
    /// </code>
    ///</summary>
    int x, y, w, h;
};
