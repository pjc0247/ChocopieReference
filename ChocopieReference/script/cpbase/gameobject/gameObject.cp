###################################################
#             ChocoPie GameEngine                 #
#                           Game Object           #
###################################################

class GameObject < RootObject
    attr_accessor :x, :y
    attr_accessor :rect, :layer
    attr_accessor :scale
    
    attr_reader :sprite
    attr_reader :step
    attr_reader :id

    attr_accessor :type

    attr_accessor :origin         
    attr_accessor :repeat

    attr_accessor :cid

    def initialize(x,y,sprite = nil)
        @x = x
        @y = y
        @step = 0
        @repeat = true
        @showRect = 0
        @collisionCheck = 0

        if @cid == nil
            @cid = 0
        end
        @type = 0

        @animate = false
        @animateAlpha = false
        @animateColor = false

        @id = 0

        @layer = 0

        @origin = Point.new(0,0)

        @rect = Rect.new(x,y)
        @scale = 1
        if sprite == nil
            @sprite = nil
            @visible = false
            @rect.w = 0
            @rect.h = 0

            @blend = NONE
            @alpha = 255
            @color = Color.White
            @angle = 0
        else
            @sprite = sprite
            @visible = true
            @rect.w = sprite.w
            @rect.h = sprite.h

            @blend = sprite.blend
            @alpha = 255
            @color = Color.White
            @angle = 0
        end
    end
    def dispose
		super

        if @collisionCheck == 1 or @collisionCheck == true
            $colmgr.delete self
        end

        if @layer != nil
            @layer.delete self
        end
    end

    def centeredOrigin
        size = @sprite.size
        @origin = Point.new(
            size.w/2,size.h/2)
    end

    def collisionCheck=(v)
        @collisionCheck = v
        if @collisionCheck == 1 or @collisionCheck == true
            $colmgr.add self
        end
    end
    def collisionCheck
        @collisionCheck
    end

    def collide(obj)
        puts "#{self} collide with #{obj}"
    end

    def blend=(mode)
        @blend = mode
        @sprite.blend = mode
    end
    def blend
        @blend
    end

    def color=(c)
        @color = c
        @sprite.color = c
    end
    def color
        @color
    end

    def alpha=(a)
        @alpha = a
        @sprite.alpha = a
    end
    def alpha
        @alpha
    end

    def angle=(a)
        @angle = a
        @sprite.angle = a
    end
    def angle
        @angle
    end

    def step=(s)
        @step = s
        if @sprite != nil and @sprite.stepW * @sprite.stepH <= s
            if @repeat == true
                @step = 0
            else
                @step -= 1
            end
        end
    end
    def doStep
        self.step = @step+1
    end

    def rect
        @rect.x = @x
        @rect.y = @y
        return @rect * @scale
    end
    def scaleRect(m)
        
    end

    def position
        return Point.new(@x,@y)
    end
    def pos
        return Point.new(@x,@y)
    end


    def applyColor(s=nil)
        if s == nil
            dst = @sprite
        else
            dst = s
        end

        dst.color = Color.new(
            (@color.r*(1.0/255.0)) * (@layer.color.r*(1.0/255.0)) * 255,
            (@color.g*(1.0/255.0)) * (@layer.color.g*(1.0/255.0)) * 255,
            (@color.b*(1.0/255.0)) * (@layer.color.b*(1.0/255.0)) * 255)

    end
    def applyAlpha(s=nil)
        if s == nil
            dst = @sprite
        else
            dst = s
        end

        dst.alpha = (@alpha*(1.0/255.0)) * (@layer.alpha*(1.0/255.0)) * 255
    end
    def applyAngle(s=nil)
        if s == nil
            dst = @sprite
        else
            dst = s
        end

        dst.angle = @angle
    end
    def applyBlend(s=nil)
        if s == nil
            dst = @sprite
        else
            dst = s
        end

        dst.blend = @blend
    end

    def applyAttributes
        @sprite.step = @step
        applyColor
        applyAlpha
        applyAngle
        applyBlend
    end

    def drawRect
        $graphic.color = Color.Red
        $graphic.rect(
            rect.x,rect.y,rect.w,rect.h)
    end
    def draw(x=0,y=0)
        self.applyAttributes
        @sprite.draw(x,y)

        if @showRect == true
            drawRect
        end
    end
    def update
        if @visible == true
            self.draw(
                @x - @origin.x,
                @y - @origin.y)
        end

        if @animate == true
            ## 타게팅 애니메이션인 경우
            if @animateType == ByTarget
                stepX = (@animateTarget.x - @x).to_f / @animateFrame
                stepY = (@animateTarget.y - @y).to_f / @animateFrame

                @x += stepX
                @y += stepY

                if (@x.to_i == @animateTarget.x and
                    @y.to_i == @animateTarget.y)
                    self.optimizePosition
                    @animate = false
                end
            ## 그 외의 경우 (방향, 지점)
            else
                @x += @animateStepX
                @y += @animateStepY

                @animateFrame -= 1
                if @animateFrame == 0
                    self.optimizePosition
                    @animate = false
                end
            end
        end
        if @animateAlpha == true
            @alpha += @animateStepAlpha
            if @alpha == @animateDestAlpha
                @animateAlpha = false
            end
        end
        if @animateColor == true
            @color.r += @animateStepR
            @color.g += @animateStepG
            @color.b += @animateStepB
            @animateFrame += 1

            if @animateFrame >= @animateDestFrame
                @animateColor = false
            end
        end
    end


    ## 알파값으로 애니메이트
    def animateByAlpha(alpha,frame)
        @animateDestAlpha = alpha
        @animateStepAlpha = (alpha.to_f - @alpha.to_f) / frame.to_f
        @animateAlpha = true
    end
    ## 칼라로 애니메이트
    def animateByColor(color,frame)
        @animateDestR = color.r
        @animateDestG = color.g
        @animateDestB = color.b
        @animateStepR = (color.r.to_f - @color.r.to_f) / frame.to_f
        @animateStepG = (color.g.to_f - @color.g.to_f) / frame.to_f
        @animateStepB = (color.b.to_f - @color.b.to_f) / frame.to_f
        @animateColor = true
        @animateFrame = 0
        @animateDestFrame = frame
    end

    ## 방향을 기준으로 애니메이트
    def animateByDirection(direction,distance,frame)
        distance = distance.to_f

        @animateType = ByDirection
        @animateDirection = direction
        @animateDistance = distance
        @animateFrame = frame
        @animateStepX = 0
        @animateStepY = 0

        if direction == DOWN
            @animateStepY = (distance / frame)
        elsif direction == UP
            @animateStepY = -(distance / frame)
        elsif direction == LEFT
            @animateStepX = -(distance / frame)
        elsif direction == RIGHT
            @animateStepX = (distance / frame)
        end

        @animate = true
    end
    ## 위치를 기준으로 애니메이트
    def animateByPosition(pos,frame)
        @animateType = ByPosition
        @animateFrame = frame
        
        @animateDistanceX = pos.x - @x
        @animateDistanceY = pos.y - @y

        @animateStepX = @animateDistanceX.to_f / frame
        @animateStepY = @animateDistanceY.to_f / frame

        @animate = true
    end
    ## 타겟을 기준으로 애니메이트
    def animateByTarget(obj,frame)
        @animateType = ByTarget
        @animateTarget = obj
        @animateFrame = frame

        @animate = true
    end

    def optimizePosition
        @x = @x.round
        @y = @y.round
    end
end

