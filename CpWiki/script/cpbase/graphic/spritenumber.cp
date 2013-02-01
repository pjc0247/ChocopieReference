###################################################
#             ChocoPie GameEngine                 #
#                           Sprite Number         #
###################################################

class SpriteNumber
    attr_accessor :color, :alpha, :angle

    def initialize(img)
        @sprite = Sprite.new(img,10)

        @color = Color.White
        @alpha = 255
        @angle = 0
    end
    def dispose
        @sprite.dispose
    end

    def draw(x,y,num)
        str = String(num)

        length = str.length - 1

        @sprite.angle = @angle
        @sprite.color = @color
        @sprite.alpha = @alpha 

        for i in 0..length
            @sprite.step = num%10

            @sprite.draw(
                x+@sprite.w * (length-i), y)
            num /= 10
        end
    end
end

