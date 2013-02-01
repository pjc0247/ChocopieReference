## 슈퍼 패스트
## 물리 속도가 상승한다
class Scene < SceneBase
    def startEvent
        @event = true
        @eventDuration = 6000
        @eventStartTick = getTicks
        @eventState = 0

        @eventTimer = Timer.new(@eventDuration)
        @eventTimer.start

        @red = Sprite.new("red.png")

        @superFast = true
        @backAlpha = 0
        @backAlphaD = 1
    end
    def endEvent
        @event = false

        @nextEvent.stop
        @nextEvent.interval = rand(6000) + 3000
        @nextEvent.start


        @eventTimer.dispose
        @red.dispose

        @superFast = false
    end
    def updateEvent
        @backAlpha += @backAlphaD
        if @backAlphaD == 1
            if @backAlpha == 180
                @backAlphaD = - 1
            end
        elsif @backAlphaD == -1
            if @backAlpha == 100
                @backAlphaD = 1
            end
        end
        @red.alpha = @backAlpha

        if @eventTimer.done
            endEvent
        end
    end
end