###################################################
#             ChocoPie GameEngine                 #
#                           Window Manager        #
###################################################

class WindowManager
    attr_accessor :layer
    attr_reader :w

    def initialize
        @w = {}    
        @layer = 0
        @idx = []
    end
    def dispose
    end

    # 윈도우 리스트에 새 윈도우를 등록합니다
    def add(w)
        @w[w] = w
        w.idx = @idx.size
        @idx[@idx.size] = w
    end
    # 윈도우 리스트에서 해당하는 윈도우를 제거합니다.
    def delete(w)
        @w.delete w
    end

    # 윈도우 리스트들에 있는 윈도우들을 업데이트합니다.
    def update
        @w.each do |key,value|
            value.update
        end
    end
     
    def focusNext
        if getFocus == nil
            return
        end
        if @idx[getFocus.idx+1] != nil
            setFocus @idx[getFocus.idx+1]
        end
    end

    def event(e,arg)
        focusChanged = false

        @w.each do |key,value|
                if value.layer.freezed == false

                if e >= LBUTTONDOWN and e <= MOUSEMOVE
                    if HasIntersection(value.rect,
                                        Rect.new(arg.x,arg.y,1,1))
                    
                        targ = MouseMove.new
                        targ.x = arg.x - value.x
                        targ.y = arg.y - value.y

                        if value.hovered == false
                            value.hovered = true
                            value.event(MOUSEHOVER,targ)
                        end
                        value.event(e,targ)
                    else
                        if value.hovered == true
                            targ = MouseMove.new
                            targ.x = arg.x - value.x
                            targ.y = arg.y - value.y

                            value.hovered = false
                            value.event(MOUSELEAVE,targ)
                        end
                    end
                elsif e >= KEYDOWN and e <= KEYUP
                    if value.focused
                        if e == KEYDOWN and focusChanged == false
                            if arg.key == TAB
                                focusChanged = true
                                focusNext
                            end
                        else
                            value.event(e,arg)
                        end
                    end
                end
            end
        end
    end
end