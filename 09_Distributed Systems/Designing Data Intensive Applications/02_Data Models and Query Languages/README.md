# 데이터 모델과 쿼리 언어

데이터 모델은 소프트웨어 개발에서 가장 중요한 부분을 차지한다. 데이터 모델은 소프트웨어 작성 방식 뿐만 아니라, 우리가 해결하려는 문제를 생각하는 방식에도 영향을 미치기 때문이다.

대부분의 애플리케이션은 하나의 데이터 모델 위에, 또 다른 데이터 모델을 층층이 쌓아 올리는 방식으로 구축된다. 각 층에 대한 가장 중요한 질문은, "이 층의 데이터 모델은 어떻게 다음 하위 층의 데이터 모델로 표현될 수 있는가?"이다.

1. 실제 세계
  - 실제 세계(사람, 조직, 상품, 행동, 금전 흐름, 센서...)를 객체나 데이터 구조, 데이터를 조작하는 API의 형태로 모델링
2. 범용 데이터 모델
  - JSON, XML, 관계형 데이터 베이스, 그래프 모델 등, 데이터의 구조를 표현하는 방법을 결정  
3. 데이터 조작
  - 범용 데이터 모델을 메모리, 디스크, 네트워크의 바이트 단위로 표현하는 방법을 결정
4. 물리적 모델
  - 바이트를 전기 전류, 빛의 펄스 등으로 표현

각 레이어는 깨끗한 데이터 모델을 제공하므로써 하위 레이어의 복잡성을 숨겨야한다(추상화). 이는 소프트웨어 개발에 참여하는 모든 이들을 효과적으로 협력할 수 있게한다.
범용 데이터 모델, 즉 데이터베이스의 결정에 따라, 소프트웨어가 할 수 있는 일이 결정되기 때문에, 이 선택은 매우 중요하다.

이 장에서는, 데이터 저장 및 쿼리를 위한 범용 데이터 모델을 살펴본다.
  - 관계형 모델
  - 문서(Document) 모델
  - 그래프(Graph) 기반 모델

## 관계형 모델 VS 문서 모델

오늘날 가장 잘 알려진 데이터 모델은 SQL 데이터 모델로 1970년 Edgar Codd가 제안한, 관계형 모델에 기반을 두고 있다.

관계형 모델
 - 테이블(관계)로 구성
 - 각 테이블은 순서 없는 튜플(행)의 모음이다.

관계형 데이터베이스의 뿌리는 1960년대와 70년대, 메인 프레임 컴퓨터에서 수행되던 비즈니스 데이터 처리에 있다. 주로 거래 처리(Transaction Processing, 판매, 은행 거래, 항공 예약, 재고 관리 등)와 일괄 처리(Batch Processing)를 위함이었다.

관계형 모델의 목표는 깔끔한 인터페이스 뒤에 복잡한 구현 세부 사항을 숨기는 것이 목표였다.

1970년부터 1980년대 초, 관계형 모델의 대안이 되기 위해 네트워크 모델, 객체 지향 모델이 등장했으나, 관계형 모델이 그들을 지배하게 되었다. 오늘날에도 여전히 온라인 출판, 토론, 소셜 네트워킹, 전자상거래, 게임 등 여러 다양한 분야에서 사용되고 있다.

### NoSQL의 탄생

2010년대, SQL의 지배에 대항하기 위한 NoSQL이 등장했다. 'NoSQL' 이라는 이름 조차, 비관계형 데이터베이스에 관한 밋업을 위한 트위터 해시 태그가 퍼진 것(#NoSQL)이며, 현재는 'Not Only SQL'로 재해석 되었다.

NoSQL 데이터베이스 채택의 이유
- 매우 큰 데이터셋 또는 매우 높은 쓰기 처리량을 포함하여, 관계형 데이터베이스가 쉽게 달성할 수 없는 확장성
- 상업용 데이터베이스 제품보다, 무료 및 오픈 소스 소프트웨어에 대한 선호
- 관계형 모델에서 지원하지 않는 특화된 질의
- 관계형 스키마의 제약에 대한 불만과 동적이고 풍부한 데이터 모델에 대한 요구

각각의 응용 프로그램은 각기 다른 요구사항을 가지고 있다. 즉, 이제 관계형 데이터 베이스와 함께 다양한 NoSQL이 사용되는 사례가 많아지고 있다. ([Polyglot Persistence](https://www.techtarget.com/searchapparchitecture/definition/polyglot-persistence))

### 객체-관계 불일치

오늘날, 대부분의 어플리케이션은 객체 지향 프로그래밍 언어로 이루어지나, SQL은 관계형 모델이므로, 애플리케이션 코드와 데이터 베이스 모델 사이에 어색한 변환 계층이 필요해졌다.([Impedance Mismatch](https://sungsoo.github.io/2013/08/21/impedance-mismatch.html))

ActiveRecord와 Hibernate 같은 객체-관계 매핑(ORM) 프레임워크는 이러한 변환 계층에 필요한 상용구 코드를 줄여주지만, 두 모델 간의 차이점을 완전히 숨길 수는 없었다.

![LinkedIn Profile Using A Relational Schema](./static/figure%202-1.PNG)

위의 그림은, 이력서(LinkedIn Profile)을 관계형 스키마로 표현하는 방법을 보여주며 다음과 같은 특징이 있다.

- `user_id`로 전체 프로필의 고유 식별자를 부여한다.
- `first_name`, `last_name`과 같은 필드는 사용자별로 고유하므로 `users` 테이블의 열로 나타낸다.
- `positions`, `education`, `contact_info`와 같은 일대다(1:N) 관계는 여러 가지 방법으로 표현할 수 있다.
  - 전통적인 SQL 모델(1999 이전)
    - 별도의 테이블을 생성하여, `users` 테이블의 외래키로 참조한다.
  - SQL 표준 버전
    - 단일 행 내에, 다중값(XML, JSON 등 구조화된 데이터)을 저장하고 해당 문서 내부에서 질의 및 인덱싱
    - Oracle, IBM DB2, MS SQL Server, PostgreSQL 등에서 지원
  - XML, JSON 등 구조화된 데이터로 인코딩하여, 데이터베이스의 텍스트 열에 저장 후, 애플리케이션이 그 구조와 내용을 해석

이력서와 같은, 데이터 구조는 대부분 독립적인 문서로 JSON 표현이 적합할 수 있다. MongoDB, RethinkDB, CouchDB, Espresso와 같은 문서 지향 데이터베이스가 이 데이터 모델을 지원한다.

```json
{
  "user_id": 251,
  "first_name": "Bill",
  "last_name": "Gates",
  "summary": "Co-chair of the Bill & Melinda Gates... Active blogger.",
  "region_id": "us:91",
  "industry_id": 131,
  "photo_url": "/p/7/000/253/05b/308dd6e.jpg",
  "positions": [
    {"job_title": "Co-chair", "organization": "Bill & Melinda Gates Foundation"},
    {"job_title": "Co-founder, Chairman", "organization": "Microsoft"}
  ],
  "education": [
    {"school_name": "Harvard University", "start": 1973, "end": 1975},
    {"school_name": "Lakeside School, Seattle", "start": null, "end": null}
  ],
  "contact_info": {
    "blog": "http://thegatesnotes.com",
    "twitter": "http://twitter.com/BillGates"
  }
}
```

관계형 예제에서, 프로필을 가져오려면 여러 쿼리를 수행(각 테이블을 `user_id`로 쿼리)해야 하거나, 복잡한 다중 `JOIN`을 수행해야 하지만, JSON 표현에서는 모든 관련 정보가 한 곳에 있어 하나의 쿼리로 충분하다.

사용자 프로필에서 사용자의 직책, 교육 이력, 연락처 정보로의 일대다 관계는 데이터에 트리 구조를 암시하며, JSON 표현은 이 트리 구조를 명시적으로 나타낸다.

![One-to-many relationships formaing a tree structure](./static/figure%202-2.PNG)

### 다대일 관계와 다대다 관계

Figure 2-1에서 `region_id`와 `industry_id`는 `Greater Seattle Area`와 같은 문자열이 아닌, ID 값으로 등록되어 있다. 물론, 사용자 인터페이스에서 지역과 산업을 입력하는 자유 텍스트 필드가 있다면, 이를 일반 텍스트 문자열로 저장하는 것이 합리적이나, 미리 표준화된 지역, 산업을 가지고 이를 사용자에게 선택하게 하는 것이 다음과 같은 많은 장점을 가진다.

- 프로필 전반(사용자들의 프로필)에서 일관된 스타일과 이름 유지
- 여러 도시가 같은 이름을 가질 때의 모호성 방지
- 업데이트 용이성
  - 이름은 데이터베이스 한 곳에만 저장되므로, 이를 수정하기만 하면 된다.
- 현지화(Localization) 지원
  - 사이트가 다른 언어로 변경될 때, 표준화된 목록을 현지화 할 수 있다.
- 더 나은 검색
  - 예를 들어, 워싱턴 주의 자선 사업가를 검색한다면 지역 목록에 시애틀이 워싱턴에 있다는 사실이 인코딩 될 수 있다. 즉 `Greater Seattle Area`라는 문자열 만으로 알 수 없는 매칭을 할 수 있다.


ID를 사용하는 이유는, 중복의 문제를 피하기 위해서이며, 이는 데이터 베이스 정규화의 핵심 아이디어이다. 언제든 변경될 수 있는 의미 있는 데이터에 고유 식별자를 부여함으로써, 데이터가 변경되더라도, 고유 식별자는 변경되지 않기 때문에 일관성을 유지할 수 있다.

데이터를 정규화 하기 위해서는, 다대일 관계(N:1, 여러 사람이 특정 한 지역에 살거나, 여러 사람이 특정 산업에 종사)가 필요하나, 이는 문서 모델엔 적합하지 않다. 관계형 데이터베이스는 `JOIN`을 통해 다른 테이블의 ID를 참조하여 이를 구조화할 수 있으나, 문서 모델에서는 `JOIN`이 필요 없으며, 있더라도, 지원이 약한 경우가 많다. 즉, 이는 애플리케이션 코드 내에서 이를 구현해야함을 의미한다.

초기에 문서 모델을 채택하여, 기존 애플리케이션 요구 사항에 적합한 기능을 구현하더라도, 시간이 지날수록 데이터는 상호 연결되는 경향이 높다. 예를 들어 다음과 같다.

- 프로필에, 조직과 학교를 엔티티로 사용하기

![Organization, Company Entity](./static/figure%202-3.PNG)

만약, 조직(사용자의 소속 회사)이나, 학교(소속 학교) 등을 단순 문자열 대신 엔티티(데이터 모델링에 사용되는 객체)로 변경한다면, 각각의 조직과 학교는 웹사이트 링크, 로고 등의 정보를 포함할 수 있다.

- 추천 기능

소속된 회사의 상사가 한 사용자를 추천하는 기능을 생각해보자. 추천은 추천받은 사용자의 이력서에 표시되며, 추천한 사용자의 이름, 프로필 사진도 함께 표시되어야 한다.

위의 새로운 기능은 다대다(N:N) 관계의 필요성을 보여주며, 대략적인 그림은 아래와 같다. 점선 사각형 내부의 데이터는 하나의 문서(Document)로 그룹화가 가능하지만, 그 이외의 참조는 조인이 필요한 경우이다.

![Recommend](./static/figure%202-4.PNG)


## 문서 데이터베이스 모델도 역사를 반복하는가?

이러한 문제는, 비단 오늘날의 문제만은 아니다. 다대다 관계와 JOIN이 가능한 관계형 데이터베이스와 달리, 문서 데이터베이스의 관계 표현 방식에 대한 논란은 과거에도 존재했다.

1970년대, 비즈니스 데이터베이스 중 가장 인기 있었던 IBM의 IMS(정보 관리 시스템)은, 계층 모델이라 불리는 간단한 데이터 모델을 가지고 있었는데 이것은 오늘날의 JSON 구조과 매우 유사하다. 이는 문서 모델과 마찬가지로, 일대다 관계에서는 강력했으나, 다대다 관계를 어렵게 만들고 조인 또한 지원하지 않았다. 즉 개발자는 다음과 같은 두 가지 선택 중 하나를 선택해야했다.

- 데이터 중복(비정규화)를 통해 다대다 관계를 표현
- 한 레코드에서 다른 레코드 참조를 애플리케이션 코드, 즉 수동으로 해결

이러한 계층 모델의 한계를 극복하기 위해 여러 해결책이 제시되었으며, 그 중 가장 주목할만한 관계형 모델과 네트워크 모델에 대해 알아보자.

### 네트워크 모델

네트워크 모델은 데이터 시스템 언어 회의(CODASYL)라는 위원회에 의해 표준화되었고, 여러 데이터베이스 공급업체에 의해 구현되었다. 이는 CODASYL 모델이라고 알려져 있다.

네트워크 모델의 특징은 다음과 같다.

- 계층 모델은 모든 레코드가 정확히 하나의 부모를 가지나, 네트워크 모델에서는 한 레코드가 여러 부모를 가질 수 있다. 즉, 다대일 및 다대다 관계를 표현할 수 있다.
- 레코드 간의 연결은 외래 키가 아닌, 포인터와 같은 방식으로 접근할 수 있었다. 즉, 레코드에 접근하는 유일한 방법은 루트 레코드에서 연결 체인을 따라가는 것이다.(Access Path)
- 네트워크 모델의 검색 방식은 연결 리스트와 비슷하다. 즉, Root부터 원하는 레코드를 찾을 때까지 하나씩 레코드를 살피는 것이다. 다대다 관계의 세상에서는 하나의 레코드에 접근하는 경로가 많기 때문에, 개발자는 이를 기억해야 했다.

네트워크 모델의 수동 접근 경로 선택 방식은, 1970년대의 매우 제한된 하드웨어 성능을 가장 효율적으로 사용할 수 있게 했으나, 데이터베이스의 쿼리 코드를 매우 복잡하게 만들었다. 접근 경로를 변경하더라도, 수많은 쿼리 코드를 수정하고, 새로운 접근 경로를 처리하도록 해야했다. 즉, 애플리케이션의 데이터 베이스 모델을 변경하는 것을 매우 어렵게 했다.

### 관계형 모델

반면, 관계형 모델은, 관계(테이블)를 단순히 튜플(행)의 집합으로 표현한다. 데이터를 살펴보기위해 복잡한 접근 경로, 중첩 구조를 따를 필요가 없으며, 임의의 조건에 맞는 행을 선택하기만 하면 된다.

또한, 특정 열을 키로 선택하고, 그에 맞추어 특정 행을 읽을 수 있다. 다른 테이블의 참조를 걱정하지 않고도 언제든 새 행을 삽입할 수 있다.

네트워크 모델과의 가장 큰 차이점은, 쿼리의 실행 순서를 개발자가 아닌, 쿼리 최적화기(Query Optimizer)가 자동으로 선택한다는 것이다. 즉, 개발자는 접근 경로를 생각할 필요가 거의 없다.

데이터를 새로운 방식으로 쿼리하려면, 단순히 새로운 인덱스를 선언하면 되고, 쿼리는 자동으로 가장 적합한 인덱스를 사용한다.

쿼리 최적화기는 매우 복잡하지만, 이를 한 번만 구축한다면 모든 애플리케이션이 그 혜택을 누릴 수 있다. 즉 장기적으로 관계형 모델이 승리할 수 있는 주요 원인이 되었다.

### 문서 모델과의 비교

문서 모델은 한 가지 측면에서는 계층 모델로 되돌아 갔다. 즉, 부모의 레코드에 중첩된 자식 레코드(일대다 관계)를 별도의 테이블이 아닌, 부모 레코드 내에 저장하는 방식이다.

그러나 다대일, 다대다를 표현하는 방식은 관계형 모델과 근본적으로 다르지 않다. 즉, 고유 식별자로 각 레코드를 참조하며, 이는 관계형 모델에서는 외래키, 문서 모델에서는 문서 참조라고 한다. 이 식별자는 읽기 시점에 조인 또는 후속 쿼리를 통해 해결되며, 이 점에서 네트워크 모델(CODASYL)과 다르다고 볼 수 있다.

## 오늘날의 관계형 데이터베이스와 문서 데이터 베이스 비교

문서 데이터 모델을 지지하는 주요 이유는 스키마 유연성, 지역성으로 인한 성능 향상, 그리고 일부 애플리케이션에서는 애플리케이션이 사용하는 데이터 구조와 더 가깝다. 이에 반해 관계형 모델은 조인, 다대일 및 다대다 관계에 대한 더 나은 지원을 제공한다.

### 어떤 모델이 더 간단한 애플리케이션 코드를 유도하는가

- 문서 데이터베이스
  - 일대다 관계의 애플리케이션 데이터를 한 번에 로드하는 경우에 매우 적합하다.(시계열 데이터, 로그 등등)
  - 문서 내의 중첩 항목을 직접 참조할 수 없으며, `사용자.직책[1]`과 같이 계층 모델의 접근 경로 방식과 유사한 방식으로 참조해야 한다. 하지만 너무 깊지만 않으면 크게 문제되지 않는다.
  - 다대다 관계의 데이터의 경우 비정규화를 통해 해결할 수 있으나, 일관성을 위한 추가 작업이 필요하다.
  - 여러 번의 데이터 베이스 요청을 통해 조인과 유사하게 사용할 수 있으나, 일반적으로 데이터 베이스 내부의 전문화된 조인보다 느리다.

- 관계형 데이터베이스
  - 다대다, 다대일 관계의 애플리케이션 데이터에 적합하다.
  - 관계형 데이터베이스의 문서 분해 기법은 문서와 같은 구조를 여러 테이블로 분할하는 방식으로, 이는 번거로운 스키마와 복잡한 애플리케이션 코드를 초래한다.

어떤 데이터 모델이 더 간단한 애플리케이션 코드를 유도하는지는 일반적으로 말하기 어렵다. 데이터가 상호 연결된 경우, 문서 모델은 어색하고, 관계형 모델은 수용 가능하며, 그래프 모델이 가장 자연스럽다.

### 문서 모델의 스키마 유연성

문서 모델과 관계형 모델의 JSON 지원은 하나의 스키마를 강제하지 않는다. 이는 문서에 임의의 키와 값을 추가할 수 있음을 뜻하며, 클라이언트는 문서에 어떤 필드가 포함되어 있는지 보장받지 못한다는 것이다.

문서 데이터베이스는 스키마가 없다(Schemaless)라고 불리지만, 이는 오해의 소지가 있다. 데이터를 읽는 코드는 보통 어떤 구조를 가정한다. 즉 **읽기 시, 스키마(Schema-on-read)** 의 방식으로 존재한다. 이는 관계형 데이터베이스의 **쓰기 시, 스키마(Schema-on-write)** 방식과 대조되는 특징이다. 

관계형 데이터베이스는 쓰기 시, 스키마를 정적 검증(컴파일 타입 검사와 유사)하며, 문서형 데이터베이스는 읽기 시, 스키마를 동적 검증(런타임 타입 검사와 유사)하는 방식이다.

예를 들어, 각 사용자의 전체 이름을 하나의 필드에 저장하다가, 이를 `first_name`, 즉 성과 이름으로 분리하고 싶다고 가정하자. 각각의 데이터베이스에 따른 구현 방법은 다음과 같다.

- 문서형 데이터베이스
  - 단순히, 새로운 필드를 추가하고, 만약 이전 문서를 읽어야할 경우, 다음과 같이 애플리케이션 코드를 변경한다.
```javascript
if (user && user.name && !user.first_name) {
  // 2013년 12월 8일 이전에 작성된 문서에는 first_name이 없습니다.
  user.first_name = user.name.split(' ')[0];
}
```

- 관계형 데이터베이스
  - 다음과 같이 마이그레이션을 수행한다.
```sql
ALTER TABLE users ADD COLUMN first_name text;
UPDATE users SET first_name = split_part(name, ' ', 1); -- PostgreSQL
UPDATE users SET first_name = substring_index(name, ' ', 1); -- MySQL
```

스키마 변경은 느리고, 다운 타임을 요구하는 것으로 악명이 높으나, 모든 경우에 그런 것은 아니다. 대부분의 관계형 데이터베이스는 `ALTER TABLE`을 단 몇 밀리초 내에 실행한다.(MySQL은 예외적으로 전체 테이블을 복사한다.) 

 단, 큰 테이블의 UPDATE 구문은 모든 데이터베이스에서 느릴 가능성이 크다. 이를 해결하기 위해, `first_name` 필드의 기본값을 `NULL`로 설정하고 애플리케이션 코드에서 이를 채울 수 있다.

읽기 시, 스키마 접근 방식은 일관되지 않는 구조를 피할 수 없을 때, 채택하는 것이 좋다.

- 다양한 종류의 객체가 있으며, 이를 한 테이블에 넣는 것이 현실적이지 않을 때
- 데이터의 구조가 외부에서 결정되며, 언제든 구조가 변경될 가능성이 있을 때

위의 상황에서는 스키마의 강제성이 방해가 될 수 있으며, 문서형 데이터베이스에 적합할 수 있다.

### 데이터 조회의 지역성(로컬리티)

애플리케이션이 전체 문서에 자주 접근해야 하는 경우(웹페이지 랜더링), 이러한 저장 로컬리티는 성능상의 이점을 제공한다.

로컬리티의 이점은 문서의 큰 부분을 동시에 필요로 할 때만 적용된다. 문서의 일부에 접근하기 위해, 전체를 로드해야 한다면, 성능 저하가 발생한다. 또한 문서를 업데이트 해야하는 경우, 보통의 경우 전체 문서를 다시 써야 하며, 문서의 인코딩된 크기를 변경하지 않는 수정만이 쉽게 수행될 수 있다. 즉, 문서를 비교적 작게 유지하고, 문서 크기를 증가시키는 쓰기는 피하는 것이 일반적으로 권장된다.

### 문서형 데이터베이스와 관계형 데이터 베이스의 융합

관계형 데이터베이스에서 JSON과 같은 문서형 데이터 타입 지원이 점차 늘고 있다. 이는 웹 API에서 JSON의 인기가 높아지며, 다른 관계형 데이터베이스들도 JSON을 지원할 가능성이 커졌다는 의미다.

문서 데이터베이스 측면에서는 RethinkDB가 쿼리 언어에서 관계형 조인과 유사한 기능을 지원하며, 일부 MongoDB 드라이버는 데이터베이스 참조를 자동으로 해결하여(사실상 클라이언트 측에서 조인을 수행하지만, 이는 추가적인 네트워크 왕복이 필요하고 최적화가 덜 되어 데이터베이스에서 수행되는 조인보다 느릴 가능성이 있다.) 관계형 조인과 유사한 작업을 수행한다.

관계형 데이터베이스와 문서 데이터베이스는 시간이 지남에 따라 점차 유사해지고 있으며, 이는 긍정적인 현상으로 볼 수 있다. 만약 하나의 데이터베이스가 문서와 같은 처리를 하면서도 관게형 쿼리를 수행할 수 있다면, 요구사항에 가장 적합한 기능 조합을 사용할 수 있다.([MySQL JSON vs. TEXT](https://medium.com/daangn/json-vs-text-c2c1448b8b1f))


## 데이터를 위한 쿼리 언어

대부분의 프로그래밍 언어는 명령형이다. 다음은 동물의 종 목록에서 상어만을 반환하는 코드이다.

```js
function getSharks() {
  var sharks = [];
  for (var i = 0; i < animals.length; i++) {
    if (animals[i].family === "Sharks") {
      sharks.push(animals[i]);
    }
  }
  return sharks;
}
```

관계 대수에서는 다음과 같이 작성한다.

$$sharks = \sigma_{family = sharks}(animal)$$

$\sigma$는 선택 연산자로, 조건에 맞는 동물만을 반환한다. 즉 `family = sharks`인 동물들만을 반환한다. SQL은 이러한 관계 대수(Relational Algebra)의 구조를 밀접하게 따랐다.

```SQL
SELECT * FROM animals WHERE family = 'Sharks';
```

SQL이나, 관계 대수와 같은 선언형 쿼리 언어(Declarative Query Language)는 원하는 데이터의 패턴(정렬, 그룹화, 집계 등)을 지정하며, 그 목표를 달성하는 방법은 지정하지 않는다. 이는 쿼리 옵티마이저가 어떤 인덱스를 사용할지, 어떤 조인을 사용할지 그리고 각 쿼리 부분을 어떤 순서로 실행할지 결정한다. 선언형 쿼리 언어는 명령형 API보다 간결하고 작업이 쉽다.

중요한 것은 엔진의 구현 세부 사항을 숨겨 데이터 베이스 시스템에 성능 개선을 도입해도 쿼리문 자체에는 아무 영향이 없도록 한다는 점이다. 명령형 코드에서는 동물 목록의 특정 순서가 이미 코드로 표현이 되어있다. 만약, 데이터베이스가 백그라운드에서 사용하지 않는 디스크 공간을 회수하려 할 때, 레코드를 이동시켜 동물의 순서를 변경해야 한다면, 이러한 명령형 코드에서는 데이터베이스가 코드가 순서에 의존하는지 확신할 방법이 없다. 하지만 선언형 코드에서는 특정한 순서를 보장하기 않기 때문에 순서가 변경이되어도 상관이 없다.

또한, 선언형 언어는 병렬 실행에 적합하다. 명령형 코드는 특정 순서대로 수행해야 하는 지시 사항을 지정하기 때문에, 여러 코어와 기계에서 병렬화 되기 쉽지 않다. 그러나 선언형 언어는 결과의 패턴만 지정하고, 결과를 결정하는 알고리즘은 지정하지 않기 때문에 병렬 실행에 더 적합하다.


### 웹에서의 선언적 쿼리

선언형 쿼리의 장점은 데이터베이스에만 국한되지 않는다. 만약 웹사이트에서 네비게이션 항목에 `Sharks`를 선택하여 표시하고 싶다면 다음과 같이 작성한다.

```html
<ul>
  <li class="selected">
    <p>Sharks</p>
    <ul>
      <li>Great White Shark</li>
      <li>Tiger Shark</li>
      <li>Hammerhead Shark</li>
    </ul>
  </li>
  <li>
    <p>Whales</p>
    <ul>
      <li>Blue Whale</li>
      <li>Humpback Whale</li>
      <li>Fin Whale</li>
    </ul>
  </li>
</ul>
```

만약 선택된 페이지의 제목을 파란색으로 강조하고 싶다면 다음과 같이 CSS 선언형 언어를 사용할 수 있다.

```css
li.selected > p {
  background-color: blue;
}
```

만약 명령적 접근 방식을 사용해야한다면, Javscript의 DOM API를 사용해 다음과 같이 작성할 수 있다.

```js
var liElements = document.getElementsByTagName("li");
for (var i = 0; i < liElements.length; i++) {
  if (liElements[i].className === "selected") {
    var children = liElements[i].childNodes;
    for (var j = 0; j < children.length; j++) {
      var child = children[j];
      if (child.nodeType === Node.ELEMENT_NODE && child.tagName === "P") {
        child.setAttribute("style", "background-color: blue");
      }
    }
  }
}
```

허나, 이런 방식은 코드가 매우 복잡해지고, 이해하기 어려워진다. 뿐만 아니라 다음과 같은 심각한 문제가 있다.

- 선택된 클래스가 제거(사용자가 다른 페이지를 클릭)하는 경우, 파란색 배경이 제거되지 않는다.
  - 선언형 CSS와 같은 경우, 규칙이 더이상 적용되지 않으면 이를 자동으로 감지해 파란색 배경을 제거한다.
- `document.getElementsByClassName("selected")`와 같은 API를 사용하고 싶다면, 성능 향상을 위해서 코드를 다시 작성해야 한다.
  - CSS는 호환성을 건드리지 않고 성능을 향상시킬 수 있다.

마찬가지로 데이터베이스에서도 SQL과 같은 선언적 쿼리 언어가 명령형 쿼리 API보다 훨씬 더 우수한 것으로 판명되었다.

### MapReduce 쿼리

MapReduce는 대량의 데이터를 여러 대의 컴퓨터에 걸쳐 일괄 처리하기 위한 프로그래밍 모델이다. MongoDB, CouchDB를 포함한 일부 NoSQL 데이터 저장소에서 읽기 전용 쿼리를 여러 문서에 걸쳐 수행하는 메커니즘으로 지원된다.

MapReduce는 선언형 쿼리 언어와 명령형 쿼리의 중간 정도의 위치에 있다. MapReduce는 많은 함수형 프로그래밍 언어에 존재하는 `map`(또는 `collect`)와 `reduce`(또는 `fold`, `inject`) 함수에 기반을 둔다.

예를 들어, 바다에서 동물을 관찰한 기록을 데이터베이스에 기록한다고 가정하자, 월별로 상어를 몇 마리나 목격했는지 알기 위해서는 다음과 같이 쿼리를 작성할 수 있다.

```sql
SELECT date_trunc('month', observation_timestamp) AS observation_month,
sum(num_animals) AS total_animals
FROM observations
WHERE family = 'Sharks'
GROUP BY observation_month;
```

이 쿼리는 먼저 관찰 기록에서 상어 과(family)의 종만 필터링하고, 그런 다음 발생한 달 별로 관찰 기록을 그룹화하며, 마지막으로 해당 달의 모든 관찰에서 본 동물의 수를 합산한다.

이를 MongoDB의 MapReduce 기능을 사용하여 다음과 같이 표현할 수 있다.

```js
db.observations.mapReduce(
  function map() {
    var year = this.observationTimestamp.getFullYear();
    var month = this.observationTimestamp.getMonth() + 1;
    emit(year + "-" + month, this.numAnimals);
  },
  function reduce(key, values) {
    return Array.sum(values);
  },
  {
    query: { family: "Sharks" },
    out: "monthlySharkReport"
  }
);
```

위의 `mapReduce` 함수를 설명하면 다음과 같다.

- 상어 종만 고려하도록 필터를 선언적으로 지정할 수 있다(이것은 MapReduce에 대한 MongoDB의 특정 확장 기능이다).

- 자바스크립트 함수 map은 query와 일치하는 각 문서에 대해 한 번씩 호출되며, this는 문서 객체로 설정된다.

- map 함수는 키(연도와 월로 구성된 문자열, 예: "2013-12" 또는 "2014-1")와 값(해당 관찰에서 본 동물의 수)을 내보낸다.

- map에 의해 내보내진 키-값 쌍은 키별로 그룹화된다. 동일한 키(즉, 동일한 월과 연도)를 가진 모든 키-값 쌍에 대해 reduce 함수가 한 번 호출된다.

- reduce 함수는 특정 월의 모든 관찰에서 본 동물의 수를 합산한다.

- 최종 출력은 컬렉션 monthlySharkReport에 기록된다.

`observations` 컬렉션에 다음의 두 개의 문서가 있다고 하자.

```js
{
  observationTimestamp: Date.parse("Mon, 25 Dec 1995 12:34:56 GMT"),
  family: "Sharks",
  species: "Carcharodon carcharias",
  numAnimals: 3
}
{
  observationTimestamp: Date.parse("Tue, 12 Dec 1995 16:17:18 GMT"),
  family: "Sharks",
  species: "Carcharias taurus",
  numAnimals: 4
}
```

- `map` 함수는 각 문서에 대해 한 번씩 호출되어, 그 결과로 `emit('1995-12', 3)`과 `emit('1995-12', 4)`가 발생한다. 이후 `reduce` 함수는 `reduce('1995-12', [3, 4])`로 호출되어 7을 반환하게 된다.

- `map`과 `reduce` 함수는 허용되는 작업에 약간의 제한이 있다. 이 함수들은 [순수 함수](https://jeong-pro.tistory.com/23)여야 하며, 이는 입력으로 전달된 데이터만 사용하고 추가적인 데이터베이스 쿼리를 수행할 수 없으며 부작용이 없어야 한다는 것을 의미한다. 이러한 제한 덕분에 데이터베이스는 함수들을 어디서나, 어떤 순서로든 실행할 수 있으며, 실패 시 재실행할 수 있다. 그러나 이러한 제한에도 불구하고 이 함수들은 여전히 강력하다. 문자열을 파싱하고, 라이브러리 함수를 호출하고, 계산을 수행하는 등의 작업을 할 수 있다.

MapReduce는 클러스터의 여러 머신에서 분산 실행을 위한 비교적 저수준의 프로그래밍 모델이다. SQL과 같은 고수준의 쿼리 언어는 MapReduce 작업의 파이프라인으로 구현될 수 있다. 그러나 MapReduce를 사용하지 않는 많은 분산 SQL 구현도 존재한다. SQL에는 단일 머신에서 실행되어야 한다는 제약이 없으며, 분산 쿼리 실행에 대한 독점권을 MapReduce가 가지고 있는 것도 아니다.

쿼리 중간에 JavaScript 코드를 사용할 수 있다는 것은 고급 쿼리에서는 매우 유용한 기능이지만, 이는 MapReduce에만 국한되지 않는다. 일부 SQL 데이터베이스도 JavaScript 함수로 확장될 수 있다.

MapReduce의 사용상의 문제점 중 하나는 두 개의 자바스크립트 함수를 신중하게 조율해서 작성해야 한다는 점인데, 이는 단일 쿼리를 작성하는 것보다 종종 더 어렵다. 게다가, 선언적 쿼리 언어는 쿼리 최적화 프로그램이 쿼리 성능을 개선할 수 있는 더 많은 기회를 제공한다. 이러한 이유로, MongoDB는 [Aggregation Pipeline](https://www.mongodb.com/ko-kr/docs/manual/core/aggregation-pipeline/)이라는 선언적 쿼리 언어에 대한 지원을 추가했다. 이 언어를 사용하면 동일한 상어 개수를 세는 쿼리는 다음과 같다

```js
db.observations.aggregate([
  { $match: { family: "Sharks" } },
  { $group: {
    _id: {
      year: { $year: "$observationTimestamp" },
      month: { $month: "$observationTimestamp" }
    },
    totalAnimals: { $sum: "$numAnimals" }
  } }
]);
```

aggregation pipeline 언어는 표현력 면에서 SQL의 하위 집합과 비슷하지만, SQL의 영어 문장 스타일 구문이 아닌 JSON 기반 구문을 사용한다. 이는 취향의 문제일 수도 있다. 이 이야기의 교훈은 NoSQL 시스템이 우연히 SQL을 변형된 형태로 재발명할 수 있다는 것이다.

## 그래프형 데이터 모델

다대다 관계는 데이터 모델을 구분하는 중요한 요소 중 하나이다. 애플리케이션의 데이터가 대부분 일대다 관계(트리 구조 데이터)거나 레코드 간에 관계가 없을 경우 도큐먼트 모델이 적합하다. 하지만 다대다 관계가 데이터에서 매우 흔한 경우에는 어떻게 해야 할까? 관계형 모델은 단순한 다대다 관계를 처리할 수 있지만, 데이터의 연결이 복잡해지면 데이터를 그래프로 모델링하는 것이 더 자연스럽다.

그래프는 두 가지 종류의 객체로 구성된다: 정점(노드 또는 엔티티)과 간선(관계 또는 아크)이다. 많은 종류의 데이터를 그래프로 모델링할 수 있다. 일반적인 예는 다음과 같다:

- 소셜 그래프: 정점은 사람들을 나타내며, 간선은 사람들이 서로 알고 있는 관계를 나타낸다.
- 웹 그래프: 정점은 웹 페이지를 나타내며, 간선은 다른 페이지로의 HTML 링크를 나타낸다.
- 도로 또는 철도 네트워크: 정점은 교차로를 나타내며, 간선은 그 사이의 도로나 철도를 나타낸다.
잘 알려진 알고리즘이 이러한 그래프에서 작동할 수 있다. 예를 들어, 자동차 내비게이션 시스템은 도로 네트워크에서 두 지점 간의 최단 경로를 검색하며, PageRank 알고리즘은 웹 그래프에서 웹 페이지의 인기도를 결정하여 검색 결과의 순위를 매긴다.

자동차 내비게이션 시스템은 도로 네트워크에서 두 지점 간의 최단 경로를 검색하며, PageRank 알고리즘은 웹 그래프에서 웹 페이지의 인기도를 결정하여 검색 결과의 순위를 매긴다.

위에서 언급한 예제에서는 그래프의 모든 정점이 동일한 종류의 객체(사람, 웹 페이지, 도로 교차로)를 나타낸다. 그러나 그래프는 이러한 동질적인 데이터에만 국한되지 않는다. 그래프는 **완전히 다른 종류의 객체를 단일 데이터 저장소에 저장하는 일관된 방법을 제공하는 데도 강력하게 사용될 수 있다.** 예를 들어, Facebook은 사람, 위치, 이벤트, 체크인, 사용자가 작성한 댓글 등을 나타내는 다양한 종류의 정점과 친구 관계, 체크인이 발생한 위치, 누가 어떤 게시물에 댓글을 달았는지, 누가 어떤 이벤트에 참석했는지 등을 나타내는 간선을 가진 단일 그래프를 유지한다.

![Example of graph-structured data](./static/figure%202-5.PNG)

위의 그림에서, Idaho 출신의 Lucy와 프랑스 Beaune 출신의 Alain, 두 사람이 나와있다. 또한 이들은 결혼을 해서 London에 살고 있다.

그래프에서 데이터를 구조화하고 쿼리하는 여러 가지 다른 방법들이 있다. 이 섹션에서는 속성 그래프 모델(Neo4j, Titan, InfiniteGraph에서 구현됨)과 트리플 스토어 모델(Datomic, AllegroGraph 등에서 구현됨)에 대해 논의할 것이다. 또한 세 가지 선언적 그래프 쿼리 언어인 Cypher, SPARQL, Datalog에 대해 살펴볼 것이다. 이 외에도 Gremlin과 같은 명령형 그래프 쿼리 언어와 Pregel과 같은 그래프 처리 프레임워크가 있다.

### 속성 그래프(Property Graph)

속성 그래프 모델에서 각 정점(vertex)은 다음으로 구성된다

- 고유 식별자
- 나가는 간선들의 집합
- 들어오는 간선들의 집합
- 속성들의 모음 (키-값 쌍)

각 간선(edge)은 다음으로 구성된다

- 고유 식별자
- 간선이 시작되는 정점 (꼬리 정점)
- 간선이 끝나는 정점 (머리 정점)
- 두 정점 간의 관계를 설명하는 라벨
- 속성들의 모음 (키-값 쌍)

그래프 데이터베이스를 두 개의 관계형 테이블로 구성해보자. 하나는 정점(Vertex)를 위한 테이블이며, 하나는 간선(edge)를 위한 테이블이다. PostgreSQL의 JSON 데이터 타입을 사용하여, 각 속성을 저장한다.

```
CREATE TABLE vertices (
  vertex_id integer PRIMARY KEY,
  properties json
);

CREATE TABLE edges (
  edge_id integer PRIMARY KEY,
  tail_vertex integer REFERENCES vertices (vertex_id),
  head_vertex integer REFERENCES vertices (vertex_id),
  label text,
  properties json
);

CREATE INDEX edges_tails ON edges (tail_vertex);
CREATE INDEX edges_heads ON edges (head_vertex);
```

이 모델의 중요한 측면은 다음과 같다

- 어떤 정점이라도 다른 정점과 연결된 간선을 가질 수 있다. 어떤 종류의 객체가 연결될 수 있는지 제한하는 스키마가 없다.
- 주어진 정점에서 그 정점의 들어오고 나가는 간선을 효율적으로 찾을 수 있으며, 따라서 그래프를 탐색할 수 있다. 즉, 정점 체인을 따라 경로를 앞으로 또는 뒤로 따라갈 수 있다. (그래서 예제 2-2는 tail_vertex와 head_vertex 컬럼에 인덱스를 가진다.)
- 다른 종류의 관계에 대해 다른 라벨을 사용함으로써, 단일 그래프에 여러 종류의 정보를 저장할 수 있으며, 여전히 깨끗한 데이터 모델을 유지할 수 있다.

이러한 기능들은 그래프가 데이터 모델링에 있어 큰 유연성을 제공함을 보여준다. 그림 2-5는 이를 잘 설명하고 있다. 이 그림은 전통적인 관계형 스키마에서는 표현하기 어려운 몇 가지 사항을 보여준다. 예를 들어, 국가별로 다른 종류의 지역 구조(프랑스는 départements와 régions가 있고, 미국은 카운티와 주가 있다), 역사적 특이 사항(예를 들어, 국가 안에 국가가 있는 경우, 주권 국가와 나라의 복잡성을 무시함) 그리고 데이터의 다양한 세분성(Lucy의 현재 거주지는 도시로 명시되었지만, 출생지는 주 단위로만 명시됨) 등을 나타낸다.

또한 그래프를 확장하여 Lucy와 Alain 또는 다른 사람들에 관한 많은 사실을 포함시킬 수 있다고 상상할 수 있다. 예를 들어, 각 알레르겐(알레르기를 일으키는 물질)에 대해 정점을 도입하고, 사람과 알레르겐 사이에 간선을 만들어 알레르기를 나타내며, 알레르겐을 어떤 음식에 어떤 물질이 포함되어 있는지 보여주는 정점 세트와 연결할 수 있다. 그런 다음 각 사람이 먹을 수 있는 안전한 음식을 찾기 위한 쿼리를 작성할 수 있다. **그래프는 진화 가능성에 뛰어나다. 애플리케이션에 기능을 추가할 때, 그래프는 애플리케이션의 데이터 구조 변경을 쉽게 수용할 수 있도록 확장할 수 있다.**

### Cypher 쿼리 언어

Cypher는 [Neo4j 그래프 데이터베이스](https://neo4j.com/)를 위해 만들어진 선언형 쿼리 언어로, 프로퍼티 그래프에 사용된다.(영화 '매트릭스'의 캐릭터에서 따온 것이며, 암호학과는 관련 없다.)

```cypher
CREATE
(NAmerica:Location {name:'North America', type:'continent'}),
(USA:Location {name:'United States', type:'country'}),
(Idaho:Location {name:'Idaho', type:'state'}),
(Lucy:Person {name:'Lucy'}),
(Idaho) -[:WITHIN]-> (USA) -[:WITHIN]-> (NAmerica),
(Lucy) -[:BORN_IN]-> (Idaho)
```

위의 cypher 코드는 그림 2-5의 왼쪽 부분을 그래프 데이터베이스에 삽입하는 Cypher 쿼리를 보여준다. 그래프의 나머지 부분도 유사하게 추가할 수 있지만 가독성을 위해 생략되었다. 각 정점은 USA나 Idaho 같은 상징적인 이름을 부여받으며, 쿼리의 다른 부분에서 이러한 이름을 사용해 정점 간의 간선을 생성할 수 있다. 화살표 표기법을 사용하여 `(Idaho) -[
]-> (USA)`는 `WITHIN`이라는 레이블이 붙은 간선을 생성하며, `Idaho`를 꼬리 노드로, `USA`를 머리 노드로 설정한다.

그림 2-5의 모든 정점과 간선이 데이터베이스에 추가되면, 흥미로운 질문을 시작할 수 있다. 예를 들어, 미국에서 유럽으로 이주한 모든 사람의 이름을 찾는 쿼리를 작성할 수 있다. 여기서 우리는 미국 내 위치에 `BORN_IN` 간선을 가진 정점과 유럽 내 위치에 `LIVING_IN` 간선을 가진 정점을 찾아 각각의 name 프로퍼티를 반환하고자 한다.

```cypher
MATCH
(person) -[:BORN_IN]-> () -[:WITHIN*0..]-> (us:Location {name:'United States'}),
(person) -[:LIVES_IN]-> () -[:WITHIN*0..]-> (eu:Location {name:'Europe'})
RETURN person.name
```

그래프에서 패턴을 찾기 위해 MATCH 절에서 동일한 화살표 표기법이 사용된다: `(person) -[
]-> ()`는 `BORN_IN` 이라는 레이블이 붙은 간선으로 연결된 두 정점을 매칭한다. 그 간선의 꼬리 정점은 변수 `person`에 바인딩되고, 머리 정점은 이름이 지정되지 않는다.

다음 두 조건을 모두 만족하는 정점 (이를 `person`이라고 부른다)을 찾는다. 

- `person`은 어떤 정점으로 가는 `BORN_IN`이라는 출발 간선을 가진다. 그 정점으로부터, 일련의 `WITHIN` 출발 간선을 따라가면 결국 `name` 프로퍼티가 `"United States"`인 `Location` 타입의 정점에 도달한다.
- 동일한 `person` 정점은 `LIVES_IN`이라는 출발 간선도 가진다. 그 간선을 따라가고, 다시 일련의 `WITHIN` 출발 간선을 따라가면 결국 `name` 프로퍼티가 `"Europe"`인 `Location` 타입의 정점에 도달한다.

이러한 모든 `person` 정점에 대해, `name` 프로퍼티를 반환한다.

이 쿼리를 실행하는 여러 가지 방법이 있다. 여기서 설명한 방법은 데이터베이스의 **모든 사람을 스캔하고, 각 사람의 출생지와 거주지를 검사하여 조건을 만족하는 사람만 반환**하는 것이다. 하지만 동일하게, **두 Location 정점에서 시작해 역으로 작업**할 수도 있다. name 프로퍼티에 인덱스가 있다면, 미국과 유럽을 나타내는 두 정점을 효율적으로 찾을 수 있다. 그런 다음 모든 미국과 유럽의 위치(주, 지역, 도시 등)를 찾기 위해 모든 `WITHIN` 출발 간선을 따라갈 수 있다. 마지막으로, 특정 위치 정점에서 `BORN_IN` 또는 `LIVES_IN` 간선을 통해 찾을 수 있는 사람을 찾는다.

선언형 쿼리 언어에서 일반적으로 그렇듯이, 쿼리를 작성할 때 이러한 실행 세부 사항을 명시할 필요는 없다. 쿼리 최적화기가 가장 효율적일 것으로 예측되는 전략을 자동으로 선택하므로, 사용자는 나머지 애플리케이션 작성에 집중할 수 있다.


### SQL의 그래프 쿼리

그래프 데이터를 관계형 데이터로 표현할 수 있으나, 이는 다소 어렵다. 보통 관계형 데이터베이스에서는 쿼리에 필요한 조인을 미리 알고 있으나, 그래프 쿼리에서는 원하는 정점을 찾기 위한 간선이 변동하기 때문에, 필요한 조인의 수가 사전에 고정되지 않는다.

Cypher의 `() -[:WITHIN*0..] -> ()` 의 경우, **WITHIN 간선을 0번 또는 그 이상 따라가라**로 표현할 수 있지만, SQL:1999 이후로, 이러한 가변 길이 탐색은 재귀적 공통 테이블 표현식(`WITH RECURSIVE` 구문)으로 표현할 수 있다.(PostgreSQL, IBM DB2, Oracle, SQL Server 등 지원)

```sql
WITH RECURSIVE
-- in_usa is the set of vertex IDs of all locations within the United States
in_usa(vertex_id) AS (
SELECT vertex_id FROM vertices WHERE properties->>'name' = 'United States'
UNION
SELECT edges.tail_vertex FROM edges
JOIN in_usa ON edges.head_vertex = in_usa.vertex_id
WHERE edges.label = 'within'
),
-- in_europe is the set of vertex IDs of all locations within Europe
in_europe(vertex_id) AS (
SELECT vertex_id FROM vertices WHERE properties->>'name' = 'Europe'
UNION
SELECT edges.tail_vertex FROM edges
JOIN in_europe ON edges.head_vertex = in_europe.vertex_id
WHERE edges.label = 'within'
),
-- born_in_usa is the set of vertex IDs of all people born in the US
born_in_usa(vertex_id) AS (
SELECT edges.tail_vertex FROM edges
JOIN in_usa ON edges.head_vertex = in_usa.vertex_id
WHERE edges.label = 'born_in'
),
-- lives_in_europe is the set of vertex IDs of all people living in Europe
lives_in_europe(vertex_id) AS (
SELECT edges.tail_vertex FROM edges
JOIN in_europe ON edges.head_vertex = in_europe.vertex_id
WHERE edges.label = 'lives_in'
)

SELECT vertices.properties->>'name'
FROM vertices
-- join to find those people who were both born in the US *and* live in Europe
JOIN born_in_usa ON vertices.vertex_id = born_in_usa.vertex_id
JOIN lives_in_europe ON vertices.vertex_id = lives_in_europe.vertex_id;
```

1. 이름 속성의 값이 `"United States"`인 정점을 찾아 in_usa 집합의 첫 번째 요소로 만든다. `in_usa` 집합에 있는 정점들로부터 들어오는 모든 `within` 엣지를 따라가고, 이 엣지들을 모두 방문할 때까지 같은 집합에 추가한다.
2. 이와 동일하게 이름 속성의 값이 `"Europe"`인 정점으로 시작해 `in_europe` 집합을 구축
3. `in_usa` 집합에 있는 각 정점에 대해 들어오는 `born_in` 엣지를 따라가서 미국 내에서 태어난 사람들을 찾는다.
4. 마찬가지로 `in_europe` 집합에 있는 각 정점에 대해 들어오는 `lives_in` 엣지를 따라가서 유럽에 사는 사람들을 찾는다.
5. 마지막으로, 미국에서 태어난 사람들의 집합과 유럽에 사는 사람들의 집합을 조인하여 교집합을 구한다.

하나의 쿼리 언어로는 같은 쿼리를 4줄로 쓸 수 있는데 다른 쿼리 언어로는 29줄이 필요하다면, 이는 단지 서로 다른 데이터 모델이 다른 사용 사례를 만족하도록 설계되었음을 보여준다. 애플리케이션에 적합한 데이터 모델을 선택하는 것이 중요하다.


### Triple-Stores와 SPARQL

트리플 스토어 모델은 프로퍼티 그래프 모델과 거의 동등하지만, 논의할 가치가 있다. 트리플 스토어를 위한 다양한 도구와 언어가 애플리케이션 구축에 유용한 추가 요소가 될 수 있기 때문이다.

트리플 스토어에서는 모든 정보를 매우 간단한 세 부분으로 된 문장 형태로 저장한다(주어, 술어, 목적어). 예를 들어, `(Jim, likes, bananas)`라는 트리플에서 `Jim`은 주어, `likes`는 술어(동사), `bananas`는 목적어이다.

트리플의 주어는 그래프의 정점과 동등하나, 목적어는 다음의 두 가지 중 하나이다.
  - 문자열이나 숫자 같은 원시 데이터 타입의 값
    - 이 경우, 트리플의 술어와 목적어는 주어 정점의 속성의 키와 값에 해당한다. `(lucy, age, 33) == {lucy: {"age": 33}}`
  - 그래프의 또 다른 정점
    - 이 경우, 술어는 그래프의 엣지이며, 주어는 꼬리 정점, 목적어는 머리 정점이 된다. `(lucy, marriedTo, alain) == (lucy) -[:marriedTo]-> (alain)`  

그림 2-5의 데이터의 하위 집합을 [Turtle](https://en.wikipedia.org/wiki/Turtle_(syntax)) 트리플로 표현해보자
```turtle
@prefix : <urn:example:>.
_:lucy a :Person.
_:lucy :name "Lucy".
_:lucy :bornIn _:idaho.
_:idaho a :Location.
_:idaho :name "Idaho".
_:idaho :type "state".
_:idaho :within _:usa.
_:usa a :Location.
_:usa :name "United States".
_:usa :type "country".
_:usa :within _:namerica.
_:namerica a :Location.
_:namerica :name "North America".
_:namerica :type "continent".
```

위의 예시에서 정점은 `_`로 작성되며, 어떤 트리플이 동일한 정점을 참조하는지 알 수 없기 때문에 존재한다. 술어가 간선(`:bornIn`, `:within`)을 나타낸다면 목적어는 정점이 된다. 술어가 속성(`:name`, `:type`, ...)을 나타낼 때, 목적어는 문자열 리터럴이다.

위의 예시를 다음과 같이 세미콜론을 사용하여 깔끔하게 정리할 수 있다.

```turtle
_:lucy a :Person; :name "Lucy"; :bornIn _:idaho.
_:idaho a :Location; :name "Idaho"; :type "state"; :within _:usa.
_:usa a :Location; :name "United States"; :type "country"; :within _:namerica.
_:namerica a :Location; :name "North America"; :type "continent".
```
### 네트워크 모델과 비교한 그래프 데이터베이스

- CODASYL에서는 데이터베이스에 스키마가 있어서 어떤 레코드 타입이 다른 레코드 타입 내에 중첩될 수 있는지를 지정했다. 그래프 데이터베이스에서는 이러한 제한이 없다. 어떤 정점(vertex)도 다른 어떤 정점과도 엣지를 가질 수 있으며, 이는 애플리케이션이 변화하는 요구사항에 더 유연하게 적응할 수 있게 한다.
CODASYL에서는 특정 레코드에 도달하는 유일한 방법이 접근 경로를 통해서이다. 그래프 데이터베이스에서는 각 정점을 고유 ID로 직접 참조할 수 있으며, 특정 값을 가진 정점을 찾기 위해 인덱스를 사용할 수도 있다.
CODASYL에서는 레코드의 자식들이 순서가 있는 집합이어서 데이터베이스가 그 순서를 유지해야 했다. 또한 데이터베이스에 새로운 레코드를 삽입하는 애플리케이션은 이 집합 내에서 새로운 레코드의 위치를 신경 써야 했다. 그래프 데이터베이스에서는 정점과 엣지가 순서가 없으며 쿼리를 작성할 때 결과를 정렬할 수 있다.
CODASYL에서는 모든 쿼리가 명령형이었으며, 작성하기 어렵고 스키마 변경에 의해 쉽게 깨진다. 그래프 데이터베이스에서는 원한다면 명령형 코드로 순회 로직을 작성할 수 있지만, 대부분의 그래프 데이터베이스는 Cypher나 SPARQL 같은 고수준의 선언형 쿼리 언어도 지원한다.

## 쿼리 언어의 기반: Datalog

Datalog는 SPARQL이나 Cypher보다도 오래된 언어이며, 이후 쿼리 언어들이 구축된 기초를 제공했다. 실제로 Datalog는 몇몇 데이터 시스템에 사용된다.
 
Datalog는 트리플 스토어 모델과 유사하지만 조금 일반화된 형태이다. 트리플을 (주어, 술어, 객체)로 쓰는 대신 술어(주어, 목적어) 형태로 사용한다.

이전과 동일한 쿼리를 작성해보면 다음과 같이 작성할 수 있다.

```prolog
name(namerica, 'North America').
type(namerica, continent).

name(usa, 'United States').
type(usa, country).
within(usa, namerica).

name(idaho, 'Idaho').
type(idaho, state).
within(idaho, usa).

name(lucy, 'Lucy').
born_in(lucy, idaho).
```

예제 2-4를 Datalog로 표현하면 다음과 같다.

```prolog
within_recursive(Location, Name) :- name(Location, Name). /* Rule 1 */

within_recursive(Location, Name) :- within(Location, Via), /* Rule 2 */
                                    within_recursive(Via, Name).

migrated(Name, BornIn, LivingIn) :- name(Person, Name), /* Rule 3 */
                                    born_in(Person, BornLoc),
                                    within_recursive(BornLoc, BornIn),
                                    lives_in(Person, LivingLoc),
                                    within_recursive(LivingLoc, LivingIn).

?- migrated(Who, 'United States', 'Europe').
/* Who = 'Lucy'. */
```
Cypher와 SPARQL은 `SELECT`로 바로 시작하지만, Datalog는 작은 단계씩 나아간다. 우리는 데이터 베이스에 새로운 술어에 대해 알려주는 **Rule**을 정의(`within_recursive`, `migrated`) 한다. 이 술어들은 데이터베이스에 저장된 트리플이 아니라, 데이터나 다른 규칙으로부터 도출된 것이다. Rule은 다른 Rule을 참조할 수 있고, 함수가 다른 함수를 호출하거나, 재귀적으로 자신을 호출할 수 있는 것처럼, 작은 조각씩 복잡한 쿼리를 작성해나간다.

Rule에서 대문자로 시작하는 단어는 변수이며, 술어는 Cypher와 SPARQL과 일치한다. 또한 `:-` 연산자의 오른쪽에 있는 모든 술어와 일치하는 것을 찾을 수 있을 때, 규칙이 적용된다. 

![Figure 2-6](./static/figure%202-6.png)

위의 그림은 다음을 표현한다. 
1. 데이터베이스에 `name(namerica, 'North America')`가 존재하므로 Rule 1이 적용됩니다. 이는 `within_recursive(namerica, 'North America')`를 생성한다.

2. 데이터베이스에 `within(usa, namerica)`가 존재하고 이전 단계에서 `within_recursive(namerica, 'North America')`가 생성되었으므로 Rule 2가 적용된다. 이는 `within_recursive(usa, 'North America')`를 생성한다.

3. 데이터베이스에 `within(idaho, usa)`가 존재하고 이전 단계에서 `within_recursive(usa, 'North America')`가 생성되었으므로 Rule 2가 적용한다. 이는 `within_recursive(idaho, 'North America')`를 생성한다.

규칙 1과 2를 반복적으로 적용함으로써, `within_recursive` 술어는 데이터베이스에 포함된 모든 북아메리카 내의 위치(또는 다른 위치 이름)를 알려줄 수 있다.

이제, Rule 3는 특정 위치 `BornIn` 에서 태어나고 특정 위치 `LivingIn` 에서 사는 사람을 찾을 수 있다.

Datalog 접근 방식은 이 장에서 논의된 다른 쿼리 언어들과 다른 종류의 사고를 요구하지만, Rule을 다른 쿼리에서 재사용 가능하다는 점에서 매우 강력한 접근 방식이다. 단순한 일회성 쿼리보다는 데이터가 복잡한 경우에 더 잘 대응할 수 있다.

## 정리

역사적으로 데이터는 하나의 큰 트리(계층적 모델)로 표현되었지만, 이는 다대다 관계를 나타내기에 적합하지 않았기 때문에 관계형 모델이 그 문제를 해결하기 위해 발명되었다. 최근에는 개발자들이 일부 애플리케이션이 관계형 모델에도 잘 맞지 않는다는 것을 발견했다. 새로운 비관계형 "NoSQL" 데이터 스토어는 두 가지 주요 방향으로 나뉘었다:

문서 데이터베이스는 데이터가 독립된 문서로 구성되고 문서 간의 관계가 드문 경우를 목표로 한다.

그래프 데이터베이스는 정반대의 방향으로, 모든 것이 잠재적으로 모든 것과 관련될 수 있는 경우를 목표로 한다.

문서, 관계형, 그래프 이 세 가지 모델은 오늘날 널리 사용되며, 각각은 그 고유한 영역에서 뛰어나다. 한 모델은 다른 모델의 형태로 에뮬레이션될 수 있다. 예를 들어, 그래프 데이터를 관계형 데이터베이스에 표현할 수 있지만, 그 결과는 종종 어색하다. 그래서 우리는 다양한 목적에 맞는 다양한 시스템을 가지고 있으며, 모든 것을 아우르는 단일 솔루션이 없는 것이다.

문서 데이터베이스와 그래프 데이터베이스가 공통적으로 갖는 한 가지 특징은 데이터에 대한 스키마를 강제하지 않는다는 것이다. 이는 애플리케이션이 변화하는 요구사항에 적응하기 쉽게 만든다. 그러나 대부분의 애플리케이션은 여전히 데이터가 특정 구조를 가지고 있다고 가정한다. 단지 스키마가 명시적(쓰기 시 강제)인지 암시적(읽기 시 처리)인지의 문제일 뿐이다.

각 데이터 모델은 고유의 쿼리 언어 또는 프레임워크를 가지고 있으며, 우리는 여러 예시를 논의했다: SQL, MapReduce, MongoDB의 집계 파이프라인, Cypher, SPARQL, Datalog. 또한 데이터베이스 쿼리 언어는 아니지만 흥미로운 유사점을 가진 CSS와 XSL/XPath에도 간략히 언급했다.

우리가 많은 내용을 다뤘지만 여전히 언급되지 않은 데이터 모델이 많다. 몇 가지 짧은 예를 들자면:

- 유전자 데이터와 작업하는 연구자들은 종종 긴 문자열(예: DNA 분자)을 유사하지만 동일하지 않은 대규모 문자열 데이터베이스와 일치시키는 서열 유사성 검색을 수행해야 한다. 여기서 설명한 데이터베이스 중 어떤 것도 이러한 용도를 처리할 수 없기 때문에 연구자들은 GenBank와 같은 전문화된 유전자 데이터베이스 소프트웨어를 작성했다.
- 입자 물리학자들은 수십 년 동안 빅 데이터 스타일의 대규모 데이터 분석을 해왔으며, 대형 강입자 충돌기(LHC)와 같은 프로젝트는 이제 수백 페타바이트 규모로 작업한다. 이 정도 규모에서는 하드웨어 비용이 통제 불능으로 치솟지 않도록 하기 위해 맞춤형 솔루션이 필요하다.
- 전체 텍스트 검색은 데이터 모델의 일종으로, 데이터베이스와 함께 자주 사용된다. 정보 검색은 이 책에서 자세히 다루지 않을 큰 전문 분야이지만, 3장과 파트 III에서 검색 인덱스에 대해 간략히 언급할 것이다.