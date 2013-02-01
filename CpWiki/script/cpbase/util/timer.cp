﻿###################################################
#             ChocoPie GameEngine                 #
#                           Timer                 #
###################################################

class Timer
    attr_accessor :interval, :callback, :started

    def initialize(interval=0,block=nil)
        @interval = interval
        @start_tick = 0
        @pause= 0
        @callback = block
        @started = 0

        if @callback != nil
            sysobj_add(self)
        end
    end
    def dispose
        if @callback != nil
            sysobj_delete(self)
        end
    end
    
    def stop
        @pause = 1
    end
    def start
        @started = 1
        @pause = 0
        @start_tick = getTicks
    end
    def pause
        @pause = getTicks
    end
    def paused
        if @pause == 1
            return true
        else return nil
        end
    end
    def resume
        @start_tick += getTicks-@pause
        @pause = 0
    end

    def tick
        getTicks-@start_tick
    end

    def done
        # 퓨즈 중이면
        if @pause != 0 or @started == 0
            return nil
        end    

        if getTicks-@start_tick >= @interval
            if @callback == nil
                start
            end
            return 1
        else
            return nil
        end        
    end
    
    def update
        # 퓨즈 중이면
        if @pause != 0 or @started == 0
            return
        end

        if getTicks-@start_tick >= @interval
            start
            @callback.call
        end        
    end
end