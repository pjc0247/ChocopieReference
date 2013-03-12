module EventHandler
    def event(e,arg)
        super  # SceneBase.event

        case e
			when QUIT
	            self.quit
			when MOUSEMOVE
	            self.mouseMove(arg.x,arg.y,arg.state)
			when LBUTTONDOWN
				self.leftDown(arg.x,arg.y)
			when LBUTTONUP
	            self.leftUp(arg.x,arg.y)
			when RBUTTONDOWN
	            self.rightDown(arg.x,arg.y)
	        when RBUTTONUP
		       self.rightUp(arg.x,arg.y)
	        when KEYDOWN
		        self.keyDown(arg.key)
	        when KEYUP
		        self.keyUp(arg.key)
	        when MOUSEHOVER
		        self.mouseHover(arg.x,arg.y)
	        when MOUSELEAVE
		        self.mouseLeave(arg.x,arg.y)
	        when FINGERDOWN
		        self.fingerDown(arg.id,arg.x,arg.y)
	        when FINGERUP
		        self.fingerUp(arg.id,arg.x,arg.y)
	        when FINGERMOVE
		        self.fingerMove(arg.id,arg.x,arg.y)
			else
				# unknown event
        end
    end
	
    def quit
        true
    end

    def leftDown(x,y)
    end
    def leftUp(x,y)
    end
    def rightDown(x,y)
    end
    def rightUp(x,y)
    end

    def mouseMove(x,y,state)
    end

    def keyDown(key)
    end
    def keyUp(key)
    end

    def mouseHover(x,y)
    end
    def mouseLeave(x,y)
    end

    def fingerDown(id,x,y)
    end
    def fingerUp(id,x,y)
    end
    def fingerMove(id,x,y)
    end
end