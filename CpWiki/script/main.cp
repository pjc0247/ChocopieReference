###################################################
#             ChocoPie GameEngine                 #
#                           main Script           #
#  여기서부터 실제 처리가 시작됩니다.                      #
###################################################

# Cp의 기본 기능들을 포함시킵니다.
import 'cpbase/cpbase'
import 'definations.cp'
# 게임에 사용할 모든 GameObject들을 포함시킵니다.
import 'Gameobject/*'

#=================================================#
# onRender                                        #
#   화면을 다시 그려야 할 때 호출되는 함수입니다.         #
#=================================================#
def onRender
    Debug.protect do
        sysobj_update
    end
end

#=================================================#
#   게임의 초기화 코드를 작성하는 부분입니다.              #
#=================================================#
begin
    # 콘솔 창을 띄웁니다
    allocconsole

    v = getVersion

    $cp_android = 0

    # Cp 시스템의 초기화
    cpInitialize

    # 게임 창의 크기 지정
    $graphic.size = Size.new(850,400)

    # 게임 창의 이름
    $cp_window_title    = "Chocopie Wiki"

    # 첫 씬의 설정fffff
    $scene.change "view"
end