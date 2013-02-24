###################################################
#             ChocoPie GameEngine                 #
#                           Panorama              #
###################################################

class Panorama < GameObject
	attr_accessor :sx, :sy
	attr_accessor :w,  :y
	attr_accessor :scroll

	def initialize(sprite,sx=0,sy=0,w=-1,h=-1,interval=1)
		super(0,0, sprite)

		@scroll = 0
		
		@sx = sx
		@sy = sy

		@w = w==-1 ? sprite.w : w
		@h = h==-1 ? sprite.h : h

		@timer = Timer.new(interval)
		@timer.start	
	end
	def dispose
		super
	end
	
	def draw(x,y)
		for i in -1..$graphic.size.w/@w
			for j in -1..$graphic.size.h/@h
				@sprite.stretch(@x+i*@w,@y+j*@h,@w,@h)
			end
		end
	end
	def update
		super
	
		if @timer.done
			doScroll
		end
	end

	def doScroll
		@x += @sx
		@y += @sy
		
		@x %= @w
		@y %= @h
	end
	def interval
		@timer.interval
	end
	def interval=(v)
		@timer.interval = v
	end
end