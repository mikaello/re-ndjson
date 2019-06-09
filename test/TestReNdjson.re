open TestFramework;

describe("my first test suite", ({test}) =>
  test("1 + 1 should equal 2", ({expect}) =>
    expect.int(ReNdjson.Util.one() + 1).toBe(2)
  )
);

// Start tests
cli();