﻿###################################################
#             ChocoPie GameEngine                 #
#                           Event Manager         #
###################################################


class EventManager
    def initialize
    end
    def dispose
    end
    
	
    def push(e,arg)   
        if $cp_android == 1
            
            if(e == MOUSEMOVE or
                e == LBUTTONDOWN or
                e == LBUTTONUP or
                e == RBUTTONDOWN or
                e == RBUTTONUP or
                e == FINGERDOWN or
                e == FINGERUP)
            
                arg.x -= 57
                arg.y -= 69
            end

        end

		# 터치 이벤트 처리
        case e
			when FINGERDOWN
				$touch.add Finger.new(arg.id,arg.x,arg.y)
			when FINGERUP
				$touch.delete Finger.new(arg.id,arg.x,arg.y)
			when FINGERMOVE
	            $touch.move Finger.new(arg.id,arg.x,arg.y)
        end

		# WindowManager에게 이벤트를 전달
        $winmgr.event(e,arg)
		# 현재 Scene에 이벤트를 전달
        $scene.event(e,arg)
    end
end
