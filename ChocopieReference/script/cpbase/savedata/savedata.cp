import 'cpbase/savedata/prefix.cp'

class SaveData
	attr_accessor :serializer
	attr_reader :prefix
	attr_reader :fp
	
	def initialize(path = nil)
		@serializer = Marshal
		@data = Hash.new
		@prefix = Prefix.new
		@path = path

		if path != nil
			open path
		else
		end
	end
	def dispose
		close if not closed
	end

	def open(path)
		# 해당 파일이 이미 존재하면
		if File.size(path) > 0
			@fp = File.new(path, "rb+")
			@empty = false
		# 존재하지 않으면
		else
			@fp = File.new(path, "wb+")
			@empty = true
		end
		
		while not @fp.eof?
			size = @fp.read(1).unpack("C")[0]
			name = @fp.read(size)
			size = @fp.read(1).unpack("C")[0]
			obj = Marshal.load @fp.read(size)

			@data[name] = obj
		end

		return @fp
	end
	def close
		@fp.close
		@fp = nil
	end
	def closed
		@fp == nil ? nil : true
	end

	def clear
		@data.clear
	end
	def set(name, obj)
		@data[@prefix.get + name] = obj	
	end
	def get(name)
		@data[@prefix.get + name]
	end

	def []=(name,obj)
		set name,obj
	end
	def [](name)
		get name
	end

	def save
		close
		@fp = File.new(@path, "wb+")

		@data.each do |key, value|
			write key, value
		end

		@fp.flush
	end

	def existed
		@empty == false ? true : nil	
	end

	private
	def write(name, obj)
		data = Marshal.dump(obj)
		@fp.write [(@prefix.get+name).length].pack("C")
		@fp.write (@prefix.get+name)
		@fp.write [data.size].pack("C")
		@fp.write data
	end
	private
	def read(name)
		
	end
end