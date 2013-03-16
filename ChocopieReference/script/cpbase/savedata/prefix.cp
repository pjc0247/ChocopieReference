class Prefix
	def initialize(default = "")
		@prefix = default

		@ary = Array.new
	end
	def dispose	
	end

	def push(name = "")
		@ary.push name
	end
	def pop
		@ary.pop
	end
	def top
		@ary.last
	end
	def clear
		@ary.clear
	end
	def get
		p = ""
		@ary.each do |str|
			p += str + "."
		end
		p
	end	
end