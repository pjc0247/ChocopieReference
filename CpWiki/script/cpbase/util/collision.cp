###################################################
#             ChocoPie GameEngine                 #
#                           Collision Check       #
###################################################

def HasIntersection(a,b)
    if a["x"] > b["x"]
        left = b
        right = a
    else
        left = a
        right = b
    end

    if (left["x"]+left["w"]) < (right["x"]) then
        return nil
    end

    if a["y"] > b["y"]
        lower = b
        upper = a
    else
        lower = a
        upper = b
    end

    if (lower["y"]+lower["h"]) < (upper["y"])
        return nil
    end

    return 1
end
