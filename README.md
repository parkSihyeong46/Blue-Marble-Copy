# 부루마블 모작
<br>

## 프로젝트 소개

## 개요
* 통신을 사용한 멀티게임 구현

## 기술 스택
* Cpp

* Win api

* WinSock2

* Visual Studio

<br>

## 시연 영상
<details>
  <summary>플레이</summary>
  <video src="https://user-images.githubusercontent.com/71202869/246674041-98cd751a-be09-48f3-90c6-97601474954f.mp4"></video>
</details>
<details>
  <summary>강제 종료 처리</summary>
  <video src="https://user-images.githubusercontent.com/71202869/246674051-5c7fe3ae-d9d6-4288-aec6-2d2abb9411de.mp4"></video>
</details>
<details>
  <summary>정상 종료 처리</summary>
  <video src="https://user-images.githubusercontent.com/71202869/246674059-5f9f02ba-0902-4f65-bbd5-a1e695319580.mp4"></video>
</details>
<br>

## 아쉬운점
* 추가적인 이미지를 넣고 프로젝트를 종료, 시간이 지난 후 프로젝트를 확인하려 열어보았으나
솔루션의 프로젝트 중 하나 이상이 제대로 로드되지 않았다며 .vcxproj" 프로젝트를 찾을 수 없습니다.는 에러코드와 함께
프로젝트를 열 수 없는 상황을 맞이함

* 문제는 잘 알지도 못하면서 무작정 필요없을 것 같다 생각되는 확장자의 파일을 git ignore에 적었던게 큰 실수
앞으로는 해당 파일의 역할을 따로 공부하고, ignore에 들어갈 파일과 아닌 파일들을 주의해서 다뤄야겠음

* <b>한줄요약 : 프로젝트를 완성했으나 .vxcproj 파일이 없어서 프로젝트를 열수가 없음</b>
  * 이미지 넣고 깔끔하게 만들기 전 버전의 작업물의 동영상이 남아있어 해당 동영상을 게제함 

## 기타
클라이언트가 게임을 시작하면<br/>

클라이언트의 소켓id를 매칭서버에 전달하게 되고<br/>

매칭서버의 큐에서 해당 id를 가지고 있다가 게임 인원이 모두 모이면(4명) <br/>

해당 id정보를 서버로 전달하고 서버와 클라이언트간 tcp 연결이 이뤄지고<br/>

모든 연산은 서버에서 수행된다.<br/>

주사위를 돌리는 버튼을 누르면 주사위 돌리는 신호를 서버로 보내게되고<br/>

서버는 해당 신호를 받아서 랜덤값 2개를 생성한 뒤<br/>

유저들에게 브로드캐스트하여 내용을 전달한다.<br/>

건물 건축도 마찬가지로 신호를 보내고 처리하여 게임 내용을 서버에서 저장하는식으로 구현함<br/>

동기화가 안맞는 클라이언트가 있을수도 있기 때문에 턴이 끝날때 마다<br/>

서버에 저장되어 있는 정보를 바탕으로 동기화를 해준다.
