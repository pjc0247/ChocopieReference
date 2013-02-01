## 파티클
## 조그만 공들이 나와서 방해한다
class Scene < SceneBase
    def startEvent
        @event = true
        @eventDuration = 6000
        @eventStartTick = getTicks
        @eventState = 0
        
        @particle = []    
        @particleC = 0

        @blueball = Sprite.new("blueball.png")
        @blueball.map "blueball"
        
        @eventTimer = Timer.new(100)
        @eventTimer.start
    end
    def endEvent
        @event = false

        @nextEvent.stop
        @nextEvent.interval = rand(6000) + 3000
        @nextEvent.start

        @blueball.dispose

        @eventTimer.dispose
        @particle.each do |value|
            value.destroy
        end
    end
    def updateEvent
        if @eventState == 0
            
        elsif @eventState == 1
            if @blueball.alpha != 0
                @blueball.alpha -= 1
            else
                endEvent
                return
            end
        end

        if @eventState == 0 and getTicks - @eventStartTick >= @eventDuration
            @eventState = 1
        end

        if @eventTimer.done
            p = Physics.new
            p.asCircle(5)
            p.create(@ball.x,@ball.y,DYNAMIC)
            p.guideline = 1
            p.resitution = 1000
            p.bind "blueball"
            p.rescale = 1
            @particle[@particleC] = p
            @particleC += 1
        end

        @particle.each do |value|
            value.draw
        end
    end
end