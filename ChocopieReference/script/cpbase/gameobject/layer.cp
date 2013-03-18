###################################################
#             ChocoPie GameEngine                 #
#                           Layer                 #
###################################################


# 2012 5 15 - 레이어를 만들면 자동으로 오브젝트 매니저에 추가


# 레이어 클래스입니다.
# 기본적으로 게임 오브젝트들은 레이어에 포함되어 자동으로 관리됩니다.
# 레이어 자신은 ObjectManager에 의해 관리됩니다.
class Layer
    #attr_accessor :z                        # 레이어의 z-order
    attr_accessor :o                        # 레이어에 포함된 object들의 목록
    attr_accessor :visible                    # 이 레이어를 표시할 것인지?
    attr_accessor :drawOnly, :autoDispose    # 그리기 전용인지?, 자동적으로 dispose시 모든 객체들을 dispose시킬 것인지?
    attr_accessor :color, :alpha            # 레이어 색상값, 알파값
    attr_accessor :layer
    attr_reader :freezed

    def initialize(z = 0)
        @o = {}
        @z = z
        @visible = true
        @drawOnly = false
        @autoDispose = true

        @freezed = false

        @color = Color.White
        @alpha = 255

        @layer = 0

        $objmgr.add self
    end
    def dispose
        @o.each do |key,value|
            if @autoDispose == true
                puts "auto disposing : " + key.to_s
                value.dispose
            end
        end

        $objmgr.delete self
    end

    def size
        @o.size
    end

    def clear
        @o.each do |key,value|
            if @autoDispose == true
                puts "auto disposing : " + key.to_s
                value.dispose
            end
        end

        @o = nil
        @o = {}
        @visible = true
        @drawOnly = false
        @autoDispose = true

        @color = Color.White
        @alpha = 255
    end

    def add(o)
        @o[o] = o
        
        Debug.protect do                        ## GameObject가 아닌 오브젝트를 추가했을때 layer변수가 없어서 나는 에러메세지를 막기 위해
            o.layer = self
        end
    end

    def delete(o)
        @o.delete_if {|v,a| a == o }
    end
    def delete_if(&block)
        @o.delete_if &block
    end

    def getLast
        @o[@o.size-1]
    end

    def update
        if @visible == false
            ##안보이는 상태이면 아무것도 안함
        else
            @o.each do |key,value|
                if @drawOnly == true or @freezed == true
                    value.draw(value.x,value.y)
                else
                    value.update
                end
            end
        end
    end

	def frozen
		@freezed == true ? true : nil
	end

	def z
		@z
	end
	def z=(v)
		@z = v
		$objmgr.sort
	end

    def freeze
        @freezed = true
    end
    def unfreeze
        @freezed = false
    end
end