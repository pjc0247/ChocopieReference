###################################################
#             ChocoPie GameEngine                 #
#                           System Object         #
###################################################

def sysobj_add(obj)
    System.add(obj)
end
def sysobj_delete(obj)
    System.delete(obj)
end
def sysobj_update()
    System.update
end

class System
    @@o = []

    def initialize
    end
    def dispose
    end
    
    def System.add(obj)
        @@o[@@o.size] = obj
    end
    def System.delete(obj)
        @@o.delete obj
    end
    def System.update
        for i in 0..@@o.size-1
            @@o[i].update
        end    
    end
end