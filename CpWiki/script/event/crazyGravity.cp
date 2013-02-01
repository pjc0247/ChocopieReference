class Scene < SceneBase
    def startEvent
        @event = true
        @eventDuration = 6000
        @eventStartTick = getTicks
        @eventState = 0

        @eventTimer = Timer.new(1000)
        @eventTimer.start
    end
    def endEvent
        @event = false
        @eventTimer.dispose

        @nextEvent.stop
        @nextEvent.interval = rand(6000) + 3000
        @nextEvent.start

        @ball.alpha = 255
    end
    def updateEvent
        @ball.alpha = rand(255) + 100

        if getTicks - @eventStartTick >= @eventDuration
            endEvent
        end

        if @eventTimer.done
            $physics.setGravity(rand(160)-80,rand(160)-80)
        end
    end
end