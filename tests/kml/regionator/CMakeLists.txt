set(TESTS feature_list_region_handler
regionator
regionator_qid
regionator_util)

foreach(TEST ${TESTS})
  build_target(TEST
    GROUP regionator
    NAME ${TEST}_test
    DEPENDS kmlregionator)
endforeach()
