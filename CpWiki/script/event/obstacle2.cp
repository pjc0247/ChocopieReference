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
        @blueball.alpha = 255

        @eventTimer = Timer.new(1000)
        @eventTimer.start
    end
    def endEvent
        @event = false
        @blueball.dispose

        @nextEvent.stop
        @nextEvent.interval = rand(6000) + 3000
        @nextEvent.start

        @eventTimer.dispose
        @particle.each do |value|
            value.destroy
        end
    end
    def updateEvent
        if @eventState == 0
            
        elsif @eventState == 1
            endEvent
            return
        end

        if @eventState == 0 and getTicks - @eventStartTick >= @eventDuration
            @eventState = 1
        end

        if @eventTimer.done
            p = Physics.new
            p.asCircle(16)
            p.create(@ball.x,@ball.y,STATIC)
            p.guideline = 1
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