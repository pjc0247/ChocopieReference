module EventHandler
    def event(e,arg)
        super  # SceneBase.event

        if e == QUIT
            self.quit
        elsif e == MOUSEMOVE
            self.mouseMove(arg.x,arg.y,arg.state)
        elsif e == LBUTTONDOWN
            self.leftDown(arg.x,arg.y)
        elsif e == LBUTTONUP
            self.leftUp(arg.x,arg.y)
        elsif e == RBUTTONDOWN
            self.rightDown(arg.x,arg.y)
        elsif e == RBUTTONUP
            self.rightUp(arg.x,arg.y)
        elsif e == KEYDOWN
            self.keyDown(arg.key)
        elsif e == KEYUP
            self.keyUp(arg.key)
        elsif e == MOUSEHOVER
            self.mouseHover(arg.x,arg.y)
        elsif e == MOUSELEAVE
            self.mouseLeave(arg.x,arg.y)
        elsif e == FINGERDOWN
            self.fingerDown(arg.id,arg.x,arg.y)
        elsif e == FINGERUP
            self.fingerUp(arg.id,arg.x,arg.y)
        elsif e == FINGERMOVE
            self.fingerMove(arg.id,arg.x,arg.y)
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