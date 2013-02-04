class TouchManager
    attr_accessor :o

    def initialize
        @o = {}
    end
    def dispose
    end

    def add(finger)
        @o[finger] = finger
    end
    def delete(finger)
        @o.delete_if {|v,a| a == finger }
    end
    def move(finger)
        @o[finger].x = finger.x
        @o[finger].y = finger.y
    end
    def size
        @o.size
    end
end