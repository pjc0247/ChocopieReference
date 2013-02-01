class SaveData
    def initialize(file)
        @file = SaveData_.new(file)

    end
    def dispose
        @file.dispose
    end

    def set(name,v)
        @file.set(name,v)
    end
    def get(name)
        return @file.get(name)
    end
    def save
        @file.save
    end
    
end
