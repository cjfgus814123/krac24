#!/bin/bash

# ==========================================
# 1. 환경 설정 및 좌표 고정
# ==========================================
WORLD_NAME="default"  # 실행 중인 월드 이름 (변경 필요 시 수정, 예: 'vtol_world')
MODEL_ROOT="$HOME/.gz/fuel/models"

# 💡 [핵심 수정] 복잡한 파이썬 GPS 변환을 제거하고, 
# 실제 드론이 착륙하는 ROS 로컬 좌표(-22.48, -31.59)를 직접 입력합니다.
RX=-22.48
RY=-31.59

# 조난자 위치도 동일하게 설정
VX=-22.48
VY=-31.59

echo "=== [Auto Spawn] 실제 드론 착륙 좌표를 기반으로 스폰을 시작합니다 ==="
echo "   - Home   (WP1) : X=0.0, Y=0.0"
echo "   - Rescue (Box) : X=$RX, Y=$RY"
echo "   - Victim (Man) : X=$VX, Y=$VY"
echo "---------------------------------------------------------"

# ------------------------------------------
# 2. 모델 스폰 실행
# ------------------------------------------

# (1) V Marker (Home)
echo ">> (1/3) Spawning V Marker at Home (0,0)..."
gz service -s /world/$WORLD_NAME/create \
--reqtype gz.msgs.EntityFactory \
--reptype gz.msgs.Boolean \
--req "sdf_filename: \"file://$MODEL_ROOT/v_marker/model.sdf\" name: \"v_marker\" pose: {position: {x: 0.0, y: 0.0, z: 0.1}}"

sleep 1

# (2) Rescue Box (구조 바구니 등)
echo ">> (2/3) Spawning Box at Rescue Point..."
gz service -s /world/$WORLD_NAME/create \
--reqtype gz.msgs.EntityFactory \
--reptype gz.msgs.Boolean \
--req "sdf_filename: \"file://$MODEL_ROOT/box/model.sdf\" name: \"rescue_box\" pose: {position: {x: $RX, y: $RY, z: 0.5}}"

sleep 1

# (3) 초록배경
echo ">> (3/3) Spawning Background at Rescue Point..."
gz service -s /world/$WORLD_NAME/create \
--reqtype gz.msgs.EntityFactory \
--reptype gz.msgs.Boolean \
--req "sdf_filename: \"file://$MODEL_ROOT/land_marker/model.sdf\" name: \"rescue_background\" pose: {position: {x: $VX, y: $VY, z: 0.0}}"

echo "=== [완료] 스폰 작업이 끝났습니다. ==="
