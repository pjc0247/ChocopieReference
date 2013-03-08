###################################################
#             ChocoPie GameEngine                 #
#                           Sound Manager         #
###################################################

class SoundManager
    def initialize
        @a = {}
        @volume = 100
    end
    def dispose
    end
    
    def add(obj)
        @a[obj] = obj
    end
    def delete(obj)
        @a.delete_if {|v,a| a == obj }
    end

    def volume
        return @volume
    end
    def volume=(v)
        @volume = v

        @a.each do |key,value|
            key.volume = key.volume * (@volume/100)
        end
    end
end