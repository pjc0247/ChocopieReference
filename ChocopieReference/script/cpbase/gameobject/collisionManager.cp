###################################################
#             ChocoPie GameEngine                 #
#                           Collisoin Manager     #
###################################################

class CollisionManager
    def initialize
        @o = {} 
    end
    def dispose
    end

    def add(obj)
        @o[obj] = obj
    end
    def delete(obj)
        @o.delete_if {|v,a| a == obj }
    end

    def update
        @o.each do |key1,value1|
            @o.each do |key2,value2|
                if value1 != value2
                    if HasIntersection(value1.rect,value2.rect)
                        value1.collide value2
                    end
                end
            end
        end
    end
end


## 2013.01.07
class LayeredCollisionManager
    attr_reader :stress
    def initialize
        @o = {} 
    end
    def dispose
    end

    def add(obj)
        if @o[obj.cid] == nil
            @o[obj.cid] = {}
        end

        @o[obj.cid][obj] = obj
    end
    def delete(obj)
        @o[obj.cid].delete_if {|v,a| a == obj }
    end

    def update
        a = 0
        @o.each do |oid1,layer1|
            layer1.each do |key1,value1|
                @o.each do |oid2,layer2|        
                    if oid1 != oid2
                        layer2.each do |key2,value2|
                            if value1 != value2 and
                                value1.type != value2.type

                                a += 1
#puts value1.to_s + " vs " + value2.to_s
                                if HasIntersection(value1.rect,value2.rect)
                                    value1.collide value2
                                end
                            end
                        end
                    end
                end
            end
        end


        @stress = a
#puts a
    end
end