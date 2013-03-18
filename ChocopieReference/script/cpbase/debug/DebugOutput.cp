import 'cpbase/data/color.cp'

class Debug
	@@font = Font.new("cpbase\\common\\sysfont.fon", 15)
	@@font.color = Color.Red

	@@msg = Array.new

	def self.output(msg)
		@@msg.push msg
	end

	def self.drawMessage(x,y)
		y2 = 0
		@@msg.each do |msg|
			@@font.draw(x, y+y2, msg)
			y2 += 15
		end

		@@msg.clear
	end

	def font
		@@font
	end

	def self.update
	end
end