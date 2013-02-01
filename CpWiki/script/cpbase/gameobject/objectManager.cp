###################################################
#             ChocoPie GameEngine                 #
#                           Object Manager        #
###################################################

class ObjectManager

    def initialize
        @l = []
    end
    def dispose
    end

    def add(layer)
        @l.push layer

## sort
        for i in 0..@l.size-1
            for j in i..@l.size-1
                if @l[i].z < @l[j].z
                    @l[i],@l[j] = @l[j],@l[i]
                end
            end
        end
    end

    def delete(layer)
        puts @l.size
        @l.delete_if {|v,a| v == layer }
        puts @l.size
    end
    def get(z)
        @l.each do |value|
            if value.z == z
                return value
            end
        end
    end

    def update
        @l.each do |value|    
            value.update
        end
        
    end
end