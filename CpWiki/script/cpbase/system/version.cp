class Version
    attr_accessor :major, :minor, :fix

    def initialize(major=1,minor=0,fix=0)
        self.set(major,minor,fix)
    end
    def dispose
    end

    def set(major,minor,fix)
        @major = major
        @minof = minor
        @fix = fix
    end
end

def getMajorVersion
    return 1
end
def getMinorVersion
    return 42
end
def getFixVersion
    return 0
end

def getLinkedMajorVersion
    return $cp_version_major
end
def getLinkedMinorVersion
    return $cp_version_minor
end
def getLinkedFixVersion
    return 0
end

def getVersion
    ver = Version.new(
        getMajorVersion,getMinorVersion,getFixVersion)
    return ver
end
def getLinkedVersion
    ver = Version.new(
        getLinkedMajorVersion,getLinkedMinorVersion,getLinkedFixVersion)
    return ver
end