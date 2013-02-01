class Scene < SceneBase
    def startEvent
        @event = true
        @eventDuration = 6000
        @eventStartTick = getTicks
        @eventState = 0
        
        @obstacle.asCircle(80)
        @obstacle.create(160,240,STATIC)
        @obstacle.guideline = 1

        @blueball = Sprite.new("blueball.png")
        @blueball.map "blueball"
        @blueball.alpha = 0

        @obstacle.bind "blueball"
        @obstacle.rescale = 1
    end
    def endEvent
        @event = false

        @nextEvent.stop
        @nextEvent.interval = rand(6000) + 3000
        @nextEvent.start

        @blueball.dispose
        @obstacle.destroy
    end
    def updateEvent
        if @eventState == 0
            if @blueball.alpha != 255
                @blueball.alpha += 1
            end
        elsif @eventState == 1
            if @blueball.alpha != 0
                @blueball.alpha -= 1
            else
                endEvent
                return
            end
        end

        if @eventState == 0 and getTicks - @eventStartTick >= @eventDuration
            @obstacle.destroy
            @obstacle.asCircle(80)
            @obstacle.create(160,240,DYNAMIC)
            @obstacle.guideline = 1

            @eventState = 1
        end

        @obstacle.draw
    end
end