class Scene < SceneBase
    def startEvent
        @event = true
        @eventDuration = 6000
        @eventStartTick = getTicks
        @eventState = 0

        @ball2.create(@ball.x,@ball.y,DYNAMIC)
        @ball2.resitution = 10000
        @ball2.density = 2.0
        @ball2.alpha = 0
        @ball2.visible = true
    end
    def endEvent
        @event = false

        @nextEvent.stop
        @nextEvent.interval = rand(6000) + 3000
        @nextEvent.start

        @ball2.visible = false
        @ball2.destroy
    end
    def updateEvent
        if @eventState == 0
            if @ball2.alpha != 255
                @ball2.alpha += 1
            end
        elsif @eventState == 1
            if @ball2.alpha != 0
                @ball2.alpha -= 1
            else
                endEvent
            end
        end

        if getTicks - @eventStartTick >= @eventDuration
            @eventState = 1
        end

        @ball2.draw
    end
end